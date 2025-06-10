#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> mp(256);
    mp['a'] = 0;
    mp['b'] = 1;
    mp['c'] = 2;
    // 最终，我们可以获得一系列操作。即b->a, c->a, c->b
    // 成环无意义，但是如果存在某个操作b->c, c->a，相当于b->a且只有这一个特例
    // 但是本身b->a看上去比c->a亏一点，但是如果b在开头则不然，因此需要贪心
    // 我知道了，是中转时的顺序，但是如何维护这个顺序又是问题
    //
    vector<vector<int>> cnt(3, vector<int>(3));
    vector<vector<int>> trans_helper(3, vector<int>(3));
    vector<vector<int>> trans_able(3, vector<int>(3));
    string              s;
    vector<int>         prefix(4);
    cin >> s;
    for (int i = 0; i < q; i++) {
        char x_, y_;
        cin >> x_ >> y_;
        int x = mp[x_], y = mp[y_];
        cnt[x][y]++;
        if (x == 2 && y == 1) {
            prefix[0]++;
        }
        if (x == 1 && y == 2) {
            prefix[1]++;
        }
        if (x == 1 && y == 0 && prefix[0]) {
            prefix[2]++;
            prefix[0]--;
        }
        if (x == 2 && y == 0 && prefix[1]) {
            prefix[3]++;
            prefix[1]--;
        }
        // 似乎会出现竞争？不会，因为唯一性
        // 不会吗？如果它c->b b->a a->c
        // c->b 1 b->a 3
        // b->c 2 c->a 4
        // 似乎常见转移路径不存在路径冲突
    }
    for (int i = 0; i < n; i++) {
        char x_ = s[i];
        int  x  = mp[x_];
        for (int y = 0; y < x; y++) {  // 这一步一定没问题，前面固定，此位相当关键
            if (cnt[x][y]) {
                cnt[x][y]--;  // 优先直达难道错了？？
                s[i] = y + 'a';
                break;
            } else {
                int found = 0;
                // 中转票可能选择错了比如这里是b->c+c->a
                // 不对啊，不就仨元素
                // 但是优先直达感觉没问题，一方面保留了c->a的权利，一方面后面的也可以重新中转
                if (x == 2 && y == 0) {
                    if (prefix[2] && cnt[2][1] && cnt[1][0]) {
                        prefix[2]--;
                        cnt[2][1]--;
                        cnt[1][0]--;
                        found = 1;
                        s[i]  = 'a';
                    }
                } else if (x == 1 && y == 0) {
                    if (prefix[3] && cnt[1][2] && cnt[2][0]) {
                        prefix[3]--;
                        cnt[1][2]--;
                        cnt[2][0]--;
                        found = 1;
                        s[i]  = 'a';
                    }
                }

                if (found) {
                    break;
                }
            }
        }
    }
    cout << s << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
#include <array>
#include <iostream>
#include <queue>
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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int q;
    cin >> q;
    deque<array<int, 2>> que;
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int c, x;
            cin >> c >> x;
            que.pb({c, x});
        } else {
            i64 k;
            cin >> k;
            i64 ans = 0;
            while (k) {
                auto cur = que.front();
                que.pop_front();
                if (cur[0] > k) {
                    ans += k * cur[1];
                    cur[0] -= k;
                    k = 0;
                    que.push_front(cur);
                } else {
                    k -= cur[0];
                    ans += 1ll * cur[0] * cur[1];
                }
            }
            cout << ans << '\n';
        }
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
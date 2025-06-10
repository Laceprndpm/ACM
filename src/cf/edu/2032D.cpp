#include <deque>
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

int query(int a, int b)
{
    cout << "? " << a << ' ' << b << endl;
    int r;
    cin >> r;
    return r;
}

void solve()
{
    int n;
    cin >> n;
    int         heads;
    vector<int> pa(n + 1);
    for (int i = 2; i <= n; i++) {
        int res = query(1, i);
        if (res != 1) {
            heads = i - 1;
            break;
        }
    }
    vector<vector<int>> candi(heads + 1);
    for (int i = 1; i <= heads; i++) {
        candi[i].push_back(i);
    }
    candi[1].push_back(heads + 1);
    pa[heads + 1] = 1;
    deque<int> que;
    for (int i = 2; i <= heads; i++) {
        que.push_back(i);
    }
    que.push_back(1);
    for (int i = 1; i <= heads; i++) {
        pa[i] = 0;
    }
    int cur       = heads + 2;
    int firstDead = -1;
    while (!que.empty()) {
        if (cur >= n) break;
        int curhead = que.front();
        que.pop_front();
        if (query(curhead, cur) == 0) {
            que.push_back(curhead);
            pa[cur] = candi[curhead].back();
            candi[curhead].push_back(cur);
            firstDead = -1;
            cur++;
        } else {
            if (firstDead == -1) {
                firstDead = curhead;
            }
        }
    }
    if (cur < n) {
        for (; cur <= n; cur++) {
            pa[cur] = candi[firstDead].back();
            candi[firstDead].push_back(cur);
        }
    }
    cout << "! ";
    for (int i = 1; i < n; i++) {
        cout << pa[i] << ' ';
    }
    cout << endl;
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
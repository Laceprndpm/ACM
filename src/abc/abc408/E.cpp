#include <cstdint>
#include <deque>
#include <iostream>
#include <set>
#include <utility>
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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<set<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].insert({v, w});
        g[v].insert({u, w});
    }
    // vector<int> dist(n + 1, INT32_MAX);
    auto check = [&](int x) -> bool {
        vector<int> vis(n + 1);
        deque<int>  que;
        que.push_back(1);
        while (!que.empty()) {
            int cur = que.front();
            que.pop_front();
            if (vis[cur]) continue;
            vis[cur] = 1;
            for (auto [v, w] : g[cur]) {
                if ((w | x) == x) {
                    que.push_back(v);
                }
            }
        }
        return vis[n];
    };
    // check();
    int cur = INT32_MAX >> 1;
    for (int i = 29; i >= 0; i--) {
        if (check(cur & ~(1 << i))) {
            cur &= ~(1 << i);
        }
    }
    cout << cur;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
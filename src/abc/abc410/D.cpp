#include <algorithm>
#include <iostream>
#include <map>
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
    vector<vector<pair<int, i64>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        i64 w;
        cin >> u >> v;
        cin >> w;
        graph[u].push_back({v, w});
    }
    set<pair<int, i64>> mp;
    vector<i64>         ans;
    auto                dfs = [&](auto&& self, int u, i64 w) {
        if (mp.count({u, w})) return;
        mp.insert({u, w});
        for (auto [v, nw] : graph[u]) {
            self(self, v, w ^ nw);
        }
        if (u == n) ans.push_back(w);
    };
    dfs(dfs, 1, 0ll);
    sor(ans);
    if (ans.empty()) {
        cout << -1 << '\n';
    } else {
        cout << ans[0];
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
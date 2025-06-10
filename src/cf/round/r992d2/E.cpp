#include <algorithm>
#include <functional>
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

vector<vector<int>> g;
vector<int>         fa;

void solve()
{
    int n;
    int q;
    cin >> n >> q;
    g.clear();
    g.resize(n + 1);
    fa.assign(n + 1, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // auto dfs = [&](auto self, int u, int f) -> void {
    //     fa[u] = f;
    //     for (int adj : g[u]) {
    //         if (adj == f) continue;
    //         self(self, adj, u);
    //     }
    // };
    vector<int> depth(n + 1);
    vector<int> d(n + 1);
    vector<int> par(n + 1);

    function<void(int, int)> dfs = [&](int v, int p) {
        if (depth[v] == 1) d[v] = 1;
        if (depth[v] > 1) d[v] = d[par[p]] + 2 * (int)g[p].size();
        par[v] = p;
        for (int adj : g[v]) {
            if (adj == p) continue;
            depth[adj] = depth[v] + 1;
            dfs(adj, v);
        }
    };
    dfs(1, 1);
    while (q--) {
        int vi, p;
        cin >> vi >> p;
        int         res = d[vi];
        vector<int> cnt;
        while (vi != 1 && par[vi] != 1) {
            cnt.eb((int)g[par[vi]].size());
            vi = par[par[vi]];
        }
        sort(all(cnt), greater<>());
        for (int i = 0; i < min(p, sz(cnt)); i++) {
            res -= 2 * (cnt[i] - 1);
        }
        cout << res << '\n';
    }
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
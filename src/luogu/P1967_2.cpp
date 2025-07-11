#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
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

vector<int> dsu;

vector<vector<pair<int, int>>> primMST(const vector<vector<pair<int, int>>>& graph)
{
    int                                                             n = graph.size() - 1;
    vector<vector<pair<int, int>>>                                  treegraph(n + 1);
    vector<bool>                                                    vis(n + 1);
    priority_queue<array<int, 3>, vector<array<int, 3>>, less<>> pq;

    for (int u_i = 1; u_i <= n; ++u_i) {
        if (vis[u_i]) continue;
        vis[u_i] = true;
        for (auto [v, w] : graph[u_i]) {
            pq.push({w, u_i, v});
        }
        while (!pq.empty()) {
            auto [d, u, v] = pq.top();
            pq.pop();
            if (vis[v]) continue;
            vis[v] = true;
            dsu[v] = u_i;
            treegraph[u].eb(v, d);
            treegraph[v].eb(u, d);
            for (auto [vv, w] : graph[v]) {
                pq.push({w, v, vv});
            }
        }
    }

    return treegraph;
}

struct LCA {
public:
    int                                  n;
    vector<array<int, 20>>               anc;
    vector<array<int, 20>>               dp;
    vector<int>                          depth;
    const vector<vector<pair<int, int>>> graph;

    void dfs(int u)
    {
        for (auto [adj, w] : graph[u]) {
            if (anc[u][0] == adj) continue;
            depth[adj]  = depth[u] + 1;
            anc[adj][0] = u;
            dp[adj][0]  = w;
            dfs(adj);
        }
    }

    void initLCA()
    {
        for (int j = 1; j <= 18; j++) {
            for (int i = 1; i <= n; i++) {
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
                dp[i][j]  = min(dp[i][j - 1], dp[anc[i][j - 1]][j - 1]);
            }
        }
    }

public:
    LCA(const vector<vector<pair<int, int>>>& graph, vector<int> tops)
        : n(graph.size() - 1), anc(n + 1), dp(n + 1), depth(n + 1), graph(graph)
    {
        for (auto& i : anc) {
            i[0] = 0;
        }
        for (int s : tops) {
            anc[s][0] = s;
            dp[s][0]  = INF;
            depth[s]  = 0;
            dfs(s);
        }
        initLCA();
    }

    int lca(int u, int v)
    {
        if (dsu[u] != dsu[v]) return -1;
        int ans = INF;
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = 18; i >= 0; i--) {
            if (depth[anc[u][i]] >= depth[v]) {
                ans = min(ans, dp[u][i]);
                u   = anc[u][i];
            }
        }
        if (u == v) {
            return ans;
        }
        for (int i = 18; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                ans = min({ans, dp[u][i], dp[v][i]});
                u = anc[u][i], v = anc[v][i];
            }
        }
        ans = min({ans, dp[u][0], dp[v][0]});
        u = anc[u][0], v = anc[v][0];
        return ans;
    }
};

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
    vector<vector<pair<int, int>>> graph(n + 1);
    dsu.assign(n + 1, 0);
    iota(all(dsu), 0);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].eb(v, w);
        graph[v].eb(u, w);
    }
    int q;
    cin >> q;
    vector<pair<i64, i64>> query(q);
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        query[i] = {x, y};
    }
    auto        res = primMST(graph);
    vector<int> sor;
    for (int i = 1; i <= n; i++) {
        if (dsu[i] == i) {
            sor.eb(i);
        }
    }
    LCA lc(res, sor);
    for (int i = 0; i < q; i++) {
        cout << lc.lca(query[i].first, query[i].second) << '\n';
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
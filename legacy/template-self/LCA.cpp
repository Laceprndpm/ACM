/**
 * @author laceprndpm
 * @date 2025/7/14
 */
//
// 不同lca中题目差别较大
// 该代码仅供参考
//

struct LCA {
public:
    int                                  n;
    vector<array<int, 20>>               anc;
    vector<int>                          depth;
    const vector<vector<pair<int, int>>> graph;
    vector<array<int, 20>>               dp;

    void dfs(int root)
    {
        for (auto [adj, w] : graph[root]) {
            if (anc[root][0] == adj) continue;
            depth[adj]  = depth[root] + 1;
            anc[adj][0] = root;
            dp[adj][0]  = w;
            dfs(adj);
        }
    }

    void initLCA()
    {
        for (int j = 1; j <= 18; j++) {
            for (int i = 1; i <= n; i++) {
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
                dp[i][j]  = std::max(dp[i][j - 1], dp[anc[i][j - 1]][j - 1]);
            }
        }
    }

public:
    LCA(const vector<vector<pair<int, int>>>& graph, int s)
        : n(graph.size() - 1), anc(n + 1), depth(n + 1), graph(graph), dp(n + 1)
    {
        for (auto& i : anc) {
            i[0] = 0;
        }
        anc[s][0] = s;
        depth[s]  = 0;
        dfs(s);
        initLCA();
    }

    int lca_dp(int u, int v)
    {
        int ans = 0;
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = 18; i >= 0; i--) {
            if (depth[anc[u][i]] >= depth[v]) {
                ans = max(ans, dp[u][i]);
                u   = anc[u][i];
            }
        }
        if (u == v) {
            return ans;
        }
        for (int i = 18; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                ans = max({ans, dp[u][i], dp[v][i]});
                u = anc[u][i], v = anc[v][i];
            }
        }
        ans = max({ans, dp[u][0], dp[v][0]});
        u = anc[u][0], v = anc[v][0];
        assert(u == v);
        return ans;
    }
};
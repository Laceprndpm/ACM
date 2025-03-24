#include <bits/stdc++.h>
using namespace std;
using i64             = long long;
using PII             = pair<int, int>;
using Graph           = vector<vector<int>>;
constexpr int INF     = INT32_MAX;
constexpr int lgbound = 1e6;
int           lg[(int)lgbound + 1];

class LCA {
private:
    int                    n;
    vector<array<int, 20>> anc;
    vector<int>            depth;
    vector<vector<int>>    graph;

    void dfs(int root)
    {
        for (int adj : graph[root]) {
            if (anc[root][0] == adj) continue;
            depth[adj]  = depth[root] + 1;
            anc[adj][0] = root;
            dfs(adj);
        }
    }

    void initLCA()
    {
        for (int j = 1; j <= 18; j++) {
            for (int i = 1; i <= n; i++) {
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
            }
        }
    }

public:
    LCA(vector<vector<int>> graph, int s) : n(graph.size() - 1), anc(graph.size()), depth(graph.size()), graph(graph)
    {
        for (auto& i : anc) {
            i[0] = 0;
        }
        anc[s][0] = s;
        depth[s]  = 0;
        dfs(s);
        initLCA();
    }

    int lca(int u, int v)
    {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = 18; i >= 0; i--) {
            if (depth[anc[u][i]] >= depth[v]) u = anc[u][i];
        }
        if (u == v) {
            return u;
        }
        for (int i = 18; i >= 0; i--) {
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i], v = anc[v][i];
            }
        }
        return anc[u][0];
    }
};

signed main(int argc, char** argv)

{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    for (int i = 1; i <= lgbound; ++i)  // 预先算出log_2(i)+1的值，用的时候直接调用就可以了
        lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);  // 看不懂的可以手推一下
    int n, m, s;
    cin >> n >> m >> s;
    Graph graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    LCA l(graph, s);
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << l.lca(u, v) << '\n';
    }
    return 0;
}
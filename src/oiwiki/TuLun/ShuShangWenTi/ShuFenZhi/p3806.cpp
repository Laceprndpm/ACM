#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define Q int(1e7 + 7)
#define N (int)1e4 + 1
vector<bool> ok(N);
vector<int>  sz(N);
vector<int>  maxv(N);

/**
 * @brief DFS树，获取每个子树的size
 */
void dfssize(const vector<vector<pair<int, int>>>& tree, const int root)
{
    function<void(int, int)> dfs = [&](int cur, int fa) -> void {
        sz[cur] = 1;
        for (auto [adj, _] : tree[cur]) {
            if (adj == fa) continue;
            if (ok[adj]) continue;
            dfs(adj, cur);
            sz[cur] += sz[adj];
        }
    };
    dfs(root, -1);
}

/**
 * @brief 重心查找
 */

vector<int> getGraphWeightCenter(const vector<vector<pair<int, int>>>& graph, int rt, int treeRoot)
{
    int                      curMin = graph.size();
    vector<int>              center;
    function<void(int, int)> dfs = [&](int cur, int father) -> void {
        maxv[cur] = sz[treeRoot] - sz[cur];
        for (auto [adj, _] : graph[cur]) {
            if (adj == father) continue;
            if (ok[adj]) continue;
            maxv[cur] = max(maxv[cur], sz[adj]);
            dfs(adj, cur);
        }
        if (curMin > maxv[cur]) {
            curMin = maxv[cur];
            center = vector<int>{cur};
        } else if (curMin == maxv[cur]) {
            center.push_back(cur);
        }
    };
    dfs(rt, -1);
    return center;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // #ifdef BATCH
    // freopen("/home/laceprndpm/acm/src/oiwiki/TuLun/ShuShangWenTi/ShuFenZhi/P3806_7.in", "r", stdin);
    // freopen(argv[2], "w", stdout);
    // #endif
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    vector<int> ask(m);
    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
        cin >> ask[i];
    }
    vector<int>                             stack_vec((int)1e5);
    int                                     top        = 0;
    function<void(int u, int fa, int dist)> putInStack = [&](int u, int fa, int dist) -> void {
        stack_vec[top++] = dist;
        for (const auto& [adj, w] : graph[u]) {
            if (adj == fa) continue;
            if (ok[adj]) continue;
            putInStack(adj, u, dist + w);
        }
    };
    vector<bool> bu(Q);
    bu[0]                         = true;
    function<void(int u)> maindfs = [&](int u) -> void {
        dfssize(graph, u);
        int rt = getGraphWeightCenter(graph, u, u)[0];
        u      = rt;
        for (const auto& [adj, w] : graph[u]) {
            if (ok[adj]) continue;
            int i = top;
            putInStack(adj, u, w);
            for (int q = 0; q < m; q++) {
                for (int j = i; j < top && !ans[q]; j++) {
                    if (ask[q] >= stack_vec[j]) {
                        ans[q] = bu[ask[q] - stack_vec[j]];
                    }
                }
            }
            for (int j = i; j < top; j++) {
                if (stack_vec[j] < Q) bu[stack_vec[j]] = true;
            }
        }
        while (top--) {
            if (stack_vec[top] < Q) bu[stack_vec[top]] = false;
        }
        top   = 0;
        ok[u] = true;
        for (auto [adj, _] : graph[u]) {
            if (!ok[adj]) {
                maindfs(adj);
            }
        }
    };
    maindfs(1);
    for (int i = 0; i < m; i++) {
        cout << (ans[i] ? "AYE\n" : "NAY\n");
    }
    return 0;
}
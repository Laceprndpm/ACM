#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 * @brief 按照树的层数进行剖分，root在0索引层
 */
vector<vector<int>> getHeightLevel(const vector<vector<int>>& graph, const vector<int>& root)
{
    vector<vector<int>>           level;
    function<void(int, int, int)> dfs = [&](int cur, int fater, int depth) -> void {
        if ((int)level.size() <= depth) {
            level.push_back(vector<int>());
        }
        level[depth].push_back(cur);
        for (int i : graph[cur]) {
            if (i == fater) continue;
            dfs(i, cur, depth + 1);
        }
    };
    for (int i : root) {
        dfs(i, -1, 0);
    }
    return level;
}

/**
 * @brief DFS树，获取每个子树的size
 */
vector<int> dfssize(const vector<vector<int>>& tree, const vector<int> root)
{
    vector<int>              sz(tree.size());
    function<void(int, int)> dfs = [&](int cur, int fa) -> void {
        sz[cur] = 1;
        for (int i : tree[cur]) {
            if (i == fa) continue;
            dfs(i, cur);
            sz[cur] += sz[i];
        }
    };
    for (int i : root) {
        dfs(i, -1);
    }
    return sz;
}

/**
 * @brief 重心查找
 */
vector<int> getGraphWeightCenter(const vector<vector<int>>& tree)
{
    auto                     sz     = dfssize(tree, {1});
    int                      curMin = tree.size();
    vector<int>              maxv(tree.size());
    vector<int>              center;
    function<void(int, int)> dfs = [&](int cur, int father) -> void {
        maxv[cur] = sz[1] - sz[cur];
        for (int i : tree[cur]) {
            if (i == father) continue;
            maxv[cur] = max(maxv[cur], sz[i]);
            dfs(i, cur);
        }
        if (curMin > maxv[cur]) {
            curMin = maxv[cur];
            center = vector<int>{cur};
        } else if (curMin == maxv[cur]) {
            center.push_back(cur);
        }
    };
    dfs(1, -1);
    return center;
}

vector<int> get_father(const vector<vector<int>>& graph, const vector<int> root)
{
    vector<int>              father(graph.size());
    function<void(int, int)> dfs = [&](int cur, int last) -> void {
        father[cur] = last;
        for (int adj : graph[cur]) {
            if (adj == last) continue;
            dfs(adj, cur);
        }
    };
    for (int i : root) {
        dfs(i, i);
    }
    return father;
}

bool treeIsomorphism(pair<const vector<vector<int>>&, const int> graph1,
                     pair<const vector<vector<int>>&, const int> graph2)
{
    auto&      tree1 = graph1.first;
    const auto rt1   = graph1.second;
    auto&      tree2 = graph2.first;
    const auto rt2_  = graph2.second;
    auto       tree  = tree1;
    const int  rt2   = rt2_ + tree1.size();
    for (const auto& i : tree2) {
        tree.emplace_back();
        for (int j : i) {
            tree.back().push_back(j + tree1.size());
        }
    }
    auto                lev = getHeightLevel(tree, {rt1, rt2});
    int                 h   = lev.size() - 1;
    vector<int>         tag(tree.size());
    vector<vector<int>> subtree_tags(tree.size());
    const vector<int>   f = get_father(tree, {rt1, rt2});
    for (int i = h - 1; i >= 0; i--) {
        for (int j = 0; j < (int)lev[i + 1].size(); j++) {
            int v = lev[i + 1][j];
            subtree_tags[f[v]].push_back(tag[v]);
        }

        sort(lev[i].begin(), lev[i].end(), [&](int u, int v) {
            return subtree_tags[u] < subtree_tags[v];
        });

        for (int j = 0, cnt = 0; j < (int)lev[i].size(); j++) {
            if (j && subtree_tags[lev[i][j]] != subtree_tags[lev[i][j - 1]]) ++cnt;
            tag[lev[i][j]] = cnt;
        }
    }
    return subtree_tags[rt1] == subtree_tags[rt2];
}

bool treeIsomorphism(const vector<vector<int>>& graph1, const vector<vector<int>>& graph2)
{
    auto c1 = getGraphWeightCenter(graph1);
    auto c2 = getGraphWeightCenter(graph2);
    for (int i : c1) {
        if (treeIsomorphism({graph1, i}, {graph2, c2[0]})) {
            return true;
        }
    }
    return false;
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph1(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph1[u].emplace_back(v);
        graph1[v].emplace_back(u);
    }
    vector<vector<int>> graph2(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph2[u].emplace_back(v);
        graph2[v].emplace_back(u);
    }
    if (treeIsomorphism(graph1, graph2)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

signed main(int argc, char** argv)
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
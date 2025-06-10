#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int>         father(n + 1);
    vector<vector<int>> graph(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> father[i];
        graph[father[i]].emplace_back(i);
        graph[i].emplace_back(father[i]);
    }
    auto&&              sz = dfssize(graph, {1});
    vector<int>         weight(n + 1);
    vector<int>         mostWeightSon(n + 1);
    function<void(int)> dfsSon = [&](int u) -> void {
        int cur = 0;
        for (int i : graph[u]) {
            if (i == father[u]) continue;
            dfsSon(i);
            cur = max(cur, sz[i]);
        }
        mostWeightSon[u] = cur;
    };
    function<void(int)> dfs = [&](int u) -> void {
        int total     = sz[u];
        int curCenter = -1;
        if (mostWeightSon[u] <= total / 2) curCenter = u;
        for (int i : graph[u]) {
            if (i == father[u]) continue;
            dfs(i);
            int v = weight[i];
            while (curCenter == -1 && v != u) {
                if (max(total - sz[v], mostWeightSon[v]) <= total / 2) {
                    curCenter = v;
                    break;
                }
                v = father[v];
            }
        }
        weight[u] = curCenter;
    };
    dfsSon(1);
    dfs(1);
    while (q--) {
        int query;
        cin >> query;
        cout << weight[query] << '\n';
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // #ifdef BATCH
    freopen("/home/laceprndpm/acm/dbg/test.in", "r", stdin);
    // freopen(argv[2], "w", stdout);
    // #endif
    solve();
    return 0;
}
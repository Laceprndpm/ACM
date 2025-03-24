#include <functional>
#include <map>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;

    vector<map<int, int>>          mp(n + 1);
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        graph[u].emplace_back(v, c);
    }
    // dfs+LCA
    // 每个点都有颜色，为其边的颜色
    // dfs首先获得以该点为根的子树的儿子数量
    vector<int>                          idx(n + 1);
    vector<int>                          colorNum(n + 1);
    function<vector<int>(int, int, int)> dfs1 = [&](int root, int color, int lst) {
        colorNum[] for (auto& i : graph[root])
        {
            if (i.first == lst) continue;
            idx[i.second]++;
            vector<int> a = dfs1(i.first, i.second, root);
        }
    };
    return 0;
}
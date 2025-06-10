#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
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
    int n, m;
    cin >> n >> m;
    if (n != m) {
        cout << "No\n";
        return 0;
    }
    vector<vector<int>> graph(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++, degree[v]++;
    }
    vector<bool>       vis(n + 1);
    function<i64(int)> dfs = [&](int u) -> i64 {
        i64 num = 1;
        vis[u]  = true;
        for (int adj : graph[u]) {
            if (vis[adj]) {
                continue;
            }
            num += dfs(adj);
        }
        return num;
    };
    if (dfs(1) == n && *max_element(degree.begin() + 1, degree.end()) == 2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return 0;
}
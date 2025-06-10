#include <algorithm>
#include <iostream>
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
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    for (auto& i : graph) {
        sort(i.begin(), i.end(), [&](int x, int y) {
            return degree[x] > degree[y];
        });
    }
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int x = 1; x <= degree[i]; x++) {
            i64 y = degree[graph[i][x - 1]] - 1;
            ans   = max(ans, 1 + x + x * y);
        }
    }
    cout << n - ans << '\n';
    return 0;
}
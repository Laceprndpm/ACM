#include <algorithm>
#include <cstdint>
#include <functional>
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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<i64, i64>>> graph(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        i64 w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    vector<bool> vis(n + 1);
    vis[1]                       = 1;
    i64                      ans = INT64_MAX;
    function<void(int, i64)> DFS = [&](int root, i64 val) {
        if (root == n) {
            ans = min(val, ans);
            return;
        }
        for (auto i : graph[root]) {
            i64 idx = i.first;
            i64 w   = i.second;
            if (!vis[idx]) {
                vis[idx] = true;
                DFS(idx, val ^ w);
                vis[idx] = false;
            }
        }
    };
    DFS(1, 0);
    cout << ans << '\n';
    return 0;
}
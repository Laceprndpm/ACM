#include <iostream>
#include <queue>
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
    queue<int> q;
    int        n, m;
    cin >> n >> m;
    vector<bool>        vis(n + 1);
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        // graph[v].emplace_back(u);
    }
    vector<int> dist(n + 1);
    q.push(1);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i : graph[cur]) {
            if (i == 1) {
                cout << dist[cur] + 1;
                return 0;
            }
            if (!vis[i]) {
                vis[i] = true;
                q.push(i);
                dist[i] = dist[cur] + 1;
            }
        }
    }
    cout << -1 << '\n';
    return 0;
}
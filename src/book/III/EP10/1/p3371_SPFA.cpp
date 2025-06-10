#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

vector<int> spfa(int start, const vector<vector<pair<int, int>>>& graph)
{
    vector<int>  dist(graph.size(), INF);
    vector<bool> vis(graph.size(), 0);
    dist[start] = 0, vis[start] = 1;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        vis[cur] = 0;
        for (pair<int, int> adj : graph[cur]) {
            if (dist[adj.first] > adj.second + dist[cur]) {
                dist[adj.first] = adj.second + dist[cur];
                if (!vis[adj.first]) {
                    q.push(adj.first);
                    vis[adj.first] = true;
                }
            }
        }
    }
    return dist;
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
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
    }
    vector<int> res = spfa(s, graph);
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    return 0;
}
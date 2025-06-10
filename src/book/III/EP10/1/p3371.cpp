#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& graph)
{
    vector<int> dist(graph.size(), INF);
    vector<int> vis(graph.size(), 0);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();

        if (vis[cur.second]) continue;
        vis[cur.second] = true;
        for (const pair<int, int>& adj : graph[cur.second]) {
            if (adj.second + cur.first < dist[adj.first]) {
                dist[adj.first] = adj.second + cur.first;
                pq.push(pair<int, int>(dist[adj.first], adj.first));
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
    vector<int> res = dijkstra(s, graph);
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& graph)
{
    vector<int> dist(graph.size(), INF);
    dist[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        pair<int, int> cur = pq.top();
        pq.pop();
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
    int n, m, k;
    int s, t;
    cin >> n >> m >> k;
    cin >> s >> t;
    vector<vector<pair<int, int>>> graph((n + 1) * (k + 1));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);

        for (int j = 1; j <= k; j++) {
            graph[u + j * n].emplace_back(v + j * n, w);
            graph[v + j * n].emplace_back(u + j * n, w);

            graph[u + j * n - n].emplace_back(v + j * n, 0);
            graph[v + j * n - n].emplace_back(u + j * n, 0);
        }
    }
    vector<int> res = dijkstra(s, graph);
    int         ans = INT32_MAX;
    for (int i = 0; i <= k; i++) {
        ans = min(res[i * n + t], ans);
    }
    cout << ans;
    return 0;
}
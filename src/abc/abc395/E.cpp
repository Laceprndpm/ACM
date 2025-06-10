#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT64_MAX;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n, m, x;
    cin >> n >> m >> x;
    vector<vector<pair<i64, i64>>> graph(2 * (n + 1));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, 1);
        graph[v + n].emplace_back(u + n, 1);
    }
    for (int i = 1; i <= n; i++) {
        graph[i].emplace_back(i + n, x);
        graph[i + n].emplace_back(i, x);
    }
    auto dijkstra = [&](int start) {
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
        return min(dist[n], dist[2 * n]);
    };
    cout << dijkstra(1);
    // vector<array<int, 2>> dp(n + 1);  // 第i个点，且当前状况为0（没反转），1（反转）的情况
    // for (auto &i : dp) {
    //     for (int &j : i) {
    //         j = INT64_MAX / 2;
    //     }
    // }
    // auto spfa = [&](int start) {
    //     vector<bool> vis(graph.size(), 0);
    //     dp[start][0] = 0, dp[start][1] = x;
    //     vis[start] = 1;
    //     queue<int> q;
    //     q.push(start);
    //     while (!q.empty()) {
    //         int cur = q.front();
    //         q.pop();
    //         vis[cur] = 0;
    //         for (pair<int, bool> adj : graph[cur]) {
    //             int update = false;
    //             if (adj.second) {
    //                 if (dp[adj.first][0] > min(dp[cur][0] + 1, dp[cur][1] + x + 1)) {
    //                     dp[adj.first][0] = min(dp[cur][0] + 1, dp[cur][1] + x + 1);
    //                     update           = true;
    //                 }
    //             } else {
    //                 if (dp[adj.first][1] > min(dp[cur][1] + 1, dp[cur][0] + x + 1)) {
    //                     dp[adj.first][1] = min(dp[cur][1] + 1, dp[cur][0] + x + 1);
    //                     update           = true;
    //                 }
    //             }
    //             if (!vis[adj.first] && update) {
    //                 q.push(adj.first);
    //                 vis[adj.first] = true;
    //             }
    //         }
    //     }
    // };
    // spfa(1);
    // cout << min(dp[n][1], dp[n][0]);
    return 0;
}
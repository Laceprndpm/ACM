#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
#define int long long

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m, x;
    cin >> n >> m >> x;
    vector<vector<pair<int, bool>>> graph(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v, 1);
        graph[v].emplace_back(u, 0);
    }
    mt19937 rd;
    rd.seed(time(0));
    for (int i = 1; i <= n; i++) {
        shuffle(graph[i].begin(), graph[i].end(), rd);
    }
    vector<array<int, 2>> dp(n + 1);  // 第i个点，且当前状况为0（没反转），1（反转）的情况
    for (auto &i : dp) {
        for (int &j : i) {
            j = INT64_MAX / 2;
        }
    }
    auto spfa = [&](int start) {
        vector<bool> vis(graph.size(), 0);
        dp[start][0] = 0, dp[start][1] = x;
        vis[start] = 1;
        queue<int> q;
        q.push(start);
        int cnt = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            vis[cur] = 0;
            for (auto adj : graph[cur]) {
                cnt++;
                if (cnt >= 5e8) {
                    return;
                }
                int update = false;
                if (adj.second) {
                    if (dp[adj.first][0] > min(dp[cur][0] + 1, dp[cur][1] + x + 1)) {
                        dp[adj.first][0] = min(dp[cur][0] + 1, dp[cur][1] + x + 1);
                        update           = true;
                    }
                } else {
                    if (dp[adj.first][1] > min(dp[cur][1] + 1, dp[cur][0] + x + 1)) {
                        dp[adj.first][1] = min(dp[cur][1] + 1, dp[cur][0] + x + 1);
                        update           = true;
                    }
                }
                if (!vis[adj.first] && update) {
                    q.push(adj.first);
                    vis[adj.first] = true;
                }
            }
        }
    };
    spfa(1);
    cout << min(dp[n][1], dp[n][0]);
    return 0;
}
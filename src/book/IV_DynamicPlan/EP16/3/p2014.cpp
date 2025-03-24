#include <bits/stdc++.h>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
vector<int>         siInput;
vector<int>         kiInput;
vector<vector<int>> graph;
vector<vector<int>> dp(305, vector<int>(305));
int                 n, m;

void DFS(int root)  // 节点root，保留x根树枝
{
    for (int v : graph[root]) {
        DFS(v);
        for (int i = m + 1; i >= 1; i--) {  // 从大到小更新
            for (int j = 0; j < i; j++) {
                dp[root][i] = max(dp[root][i], dp[root][i - j] + dp[v][j]);
            }
        }
    }
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
    cin >> n >> m;
    siInput.resize(n + 1);
    kiInput.resize(n + 1);
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> kiInput[i] >> siInput[i];
        graph[kiInput[i]].emplace_back(i);
        dp[i][1] = siInput[i];
    }
    DFS(0);
    cout << dp[0][m + 1];
    return 0;
}
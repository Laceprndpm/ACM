#include <bits/stdc++.h>
using namespace std;
using i64                 = long long;
using PII                 = pair<int, int>;
constexpr int         INF = 1e9;
string                status;
vector<vector<int>>   graph;
vector<array<int, 2>> dp;  // dp[i][x],第i个点，在安静状态时，至少需要val个墙

void DFS(int root, int lst)
{
    int ansS = 0;
    int ansP = 0;
    for (int adj : graph[root]) {
        if (adj != lst) {
            DFS(adj, root);
            ansP += min(dp[adj][1] + 1, dp[adj][0]);
            ansS += min(dp[adj][1], dp[adj][0] + 1);
        }
    }
    if (status[root] == 'S') {
        dp[root][1] = ansS;
        dp[root][0] = INF;
    } else if (status[root] == 'P') {
        dp[root][1] = INF;
        dp[root][0] = ansP;
    } else {
        dp[root][0] = ansP;
        dp[root][1] = ansS;
    }
}

void solve()
{
    int n;
    cin >> n;
    graph.clear();
    dp.clear();
    graph.resize(n);
    dp.resize(n);
    for (int i = 2; i <= n; i++) {
        int u;
        cin >> u;
        u--;
        graph[i - 1].emplace_back(u);
        graph[u].emplace_back(i - 1);
    }
    cin >> status;
    DFS(0, -1);
    cout << min(dp[0][1], dp[0][0]) << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
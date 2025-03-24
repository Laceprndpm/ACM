#include <bits/stdc++.h>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
int                 dp[30];
int                 choose[30];
vector<vector<int>> graph;
vector<int>         num;

void DFS(int x)
{
    int kidans = 0;
    for (int i : graph[x]) {
        if (dp[i] == -1) {
            DFS(i);
        }
        if (kidans < dp[i]) {
            kidans    = dp[i];
            choose[x] = i;
        }
    }
    dp[x] = kidans + num[x];
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
    int n;
    cin >> n;
    for (int i = 0; i <= n; i++) {
        dp[i] = -1;
    }
    num.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }
    graph.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        graph[0].emplace_back(i);
    }
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int tmp;
            cin >> tmp;
            if (tmp) {
                graph[i].emplace_back(j);
            }
        }
    }
    DFS(0);
    int cur = 0;
    while (choose[cur] != 0) {
        if (cur != 0) cout << cur << ' ';
        cur = choose[cur];
    }
    cout << cur;
    cout << '\n';
    cout << dp[0];
    return 0;
}
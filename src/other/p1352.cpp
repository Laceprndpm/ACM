#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

vector<array<int, 2>> dp(6005);
vector<vector<int>>   graph;

vector<int> h;

void DFS(int x)
{
    dp[x][0] = 0;
    dp[x][1] = h[x];
    for (int i = 0; i < graph[x].size(); i++) {
        int y = graph[x][i];
        DFS(y);
        dp[x][0] += max(dp[y][0], dp[y][1]);
        dp[x][1] += dp[y][0];
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    h.resize(n);
    graph.resize(n);
    vector<bool> isRoot(n, true);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[v].emplace_back(u);
        isRoot[u] = 0;
    }
    int root;
    for (int i = 0; i < n; i++) {
        if (isRoot[i]) {
            root = i;
            DFS(i);
            break;
        }
    }
    cout << max(dp[root][1], dp[root][0]);
    return 0;
}
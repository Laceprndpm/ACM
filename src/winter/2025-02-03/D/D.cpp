#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr LL MOD = 1e9 + 7;
LL           ans = 0;
int          n, k;

LL qpow(LL n, LL q, LL mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    LL ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void dfs(int node, const vector<vector<pair<int, bool>>>& graph, vector<bool>& visited, int& count)
{
    visited[node] = true;
    count++;

    for (const auto& edge : graph[node]) {
        if (edge.second && !visited[edge.first]) {
            dfs(edge.first, graph, visited, count);
        }
    }
}

void countNodesInForest(int n, vector<vector<pair<int, bool>>>& graph)
{
    vector<bool> visited(n + 1, false);
    for (int node = 1; node <= n; ++node) {
        if (!visited[node]) {
            int count = 0;
            dfs(node, graph, visited, count);
            ans += qpow(count, k);
            ans %= MOD;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    vector<vector<pair<int, bool>>> graph(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, color;
        cin >> u >> v >> color;
        graph[u].emplace_back(v, color != 1);
        graph[v].emplace_back(u, color != 1);
    }

    countNodesInForest(n, graph);
    LL realAns = 0;
    realAns += qpow(n, k);
    realAns -= ans;
    realAns += MOD;
    realAns %= MOD;
    cout << realAns;
    return 0;
}
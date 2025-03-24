#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
vector<bool>        vis;
vector<int>         degree;
vector<int>         dp;
vector<vector<int>> graph;
int                 startpoint = -1;

int finalAns = 0;

void DFS(int cur)
{
    if (degree[cur] < 4) {
        return;
    }
    if (vis[cur]) {
        return;
    }
    int ans = 0;
    ans++;
    vis[cur] = true;
    vector<int> sub;
    for (int i : graph[cur]) {
        if (!vis[cur]) {
            DFS(i);
            sub.emplace_back(dp[i]);
        }
    }
    sort(sub.begin(), sub.end(), greater<int>());
    int k = sub.size();
    for (int i = 0; i < min(k, 3 + (startpoint == cur)); i++) {
        ans += sub[i];
    }
    dp[cur] = ans;
    if (k >= 4) {
        ans += sub[3];
        finalAns = max(finalAns, ans);
    }
    return;
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vis.resize(n, false);
    graph.resize(n, vector<int>());
    dp.resize(n, 0);
    degree.resize(n, 0);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        degree[u]++;
        degree[v]++;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    int ans = finalAns;
    if (ans == 0) {
        cout << -1 << '\n';
    } else {
        cout << ans * 3 + 2 << '\n';
    }
    return 0;
}

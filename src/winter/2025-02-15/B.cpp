#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int>         degree(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        degree[u]++;
        degree[v]++;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] >= 3) {
            ans += n - degree[i] - 1;
        }
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
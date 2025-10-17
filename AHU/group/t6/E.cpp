#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, m;
    cin >> n >> m;
    vector<int> val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    vector<int>         deg(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    if (n == 1) {
        cout << val[1] << '\n';
        return;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] >= 2) {
            int mx     = 0;
            int sec_mx = 0;
            for (auto v : adj[i]) {
                if (val[v] > mx) {
                    sec_mx = mx;
                    mx     = val[v];
                } else if (val[v] > sec_mx) {
                    sec_mx = val[v];
                }
            }
            ans = max(ans, val[i]);
            ans = max(ans, sec_mx);
        }
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--) Echo2();
}
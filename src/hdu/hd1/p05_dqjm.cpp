#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long
#define int  long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, int>>> que(n + 1);
        for (int i = 1; i <= m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            que[u].push_back({v, c});
            que[v].push_back({u, c});
        }
        map<pair<int, int>, int> dis;
        map<pair<int, int>, int> vis;

        priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<array<ll, 3>>> q;  // 点，颜色
        q.push({0, 1, 0});
        int ans = 1e18;
        while (!q.empty()) {
            auto z = q.top();
            q.pop();
            if (z[1] == n) {
                ans = min(ans, z[0]);
            }
            if (vis[{z[1], z[2]}] == 0) {
                vis[{z[1], z[2]}] = 1;
                for (auto x : que[z[1]]) {
                    if (vis[{x.first, x.second}] == 0) {
                        q.push({z[0] + (z[2] != x.second), x.first, x.second});
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
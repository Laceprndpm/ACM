#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long
#define int  long long

// gcd和lcm
ll gcd(ll a, ll b)
{
    return !b ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return a / gcd(a, b) * b;
}

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
        vector<vector<int>> graph(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> arr[i];
        }
        int                   ans = 0;
        vector<map<int, int>> dp(n + 1);

        function<void(int, int)> dfs = [&](int u, int fa) {
            if (graph[u].size() == 1 && u != 1) {
                if (m % arr[u] != 0) {
                    return;
                }
                if (arr[u] == m) {
                    ans++;
                }
                dp[u][arr[u]]++;
                return;
            }
            int len = -1, w = 0;

            for (auto x : graph[u]) {
                if (x == fa) continue;
                dfs(x, u);
                if ((int)dp[x].size() > len) {
                    len = dp[x].size();
                    w   = x;
                }
            }
            for (auto &[x, y] : dp[w]) {
                int zhi = lcm(x, arr[u]);
                if (m % (zhi) == 0) {
                    if (zhi == m) {
                        ans += y;
                    }
                    dp[u][zhi] += y;
                }
            }
            for (auto x : graph[u]) {
                if (x == w) continue;
                for (auto &[x2, y2] : dp[x]) {
                    int zhi = lcm(x2, arr[u]);
                    if (m % zhi != 0) {
                        continue;
                    }
                    for (auto &[x1, y1] : dp[u]) {
                        int tmp = lcm(zhi, x1);
                        if (m % tmp == 0) {
                            if (tmp == m) {
                                ans += y1 * y2;
                            }
                        }
                    }
                    if (zhi == m) {
                        ans += y2;
                    }
                    dp[u][zhi] += y2;
                }
            }
            if (m % arr[u] == 0) {
                dp[u][arr[u]]++;
                if (arr[u] == m) {
                    ans++;
                }
            }
        };
        dfs(1, 0);
        cout << ans << endl;
    }
    return 0;
}
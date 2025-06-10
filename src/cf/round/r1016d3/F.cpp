#include <bits/stdc++.h>

#include <functional>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for (int j = 0; j < n; j++) {
        cin >> s[j];
    }
    vector<vector<string>> network(m, vector<string>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> network[i][j];
        }
    }
    int         mx = 0;
    vector<int> vis(n);
    for (int i = 0; i < m; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (hash<string>{}(network[i][j]) == hash<string>{}(s[j])) {
                cnt++;
                vis[j] = 1;
            }
        }
        mx = max(mx, cnt);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << -1 << '\n';
            return;
        }
    }
    int ans = n + 2 * (n - mx);
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        Echo2();
}
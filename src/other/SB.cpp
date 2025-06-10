#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<int> sum(n + 1);
    int         ans = 0; 
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ans += (n - 1) * a[i] * a[i];
        sum[i] += a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        sum[i] += b[i];
        ans += (n - 1) * b[i] * b[i];
    }
    for (int i = 2; i <= n; i++)
        sum[i] += sum[i - 1];
    vector<vector<int>> dp(n + 1, vector<int>(1100, inf));  // dpi表示第i位时前i位ai的和为j的最小代价
    dp[1][a[1]] = 0;
    dp[1][b[1]] = 0;
    // cout << 987 - ans << '\n';
    for (int i = 2; i <= n; i++) {
        for (int j = 1100; j >= 0; j--) {
            if (j >= a[i] && dp[i - 1][j - a[i]] != inf)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - a[i]] + a[i] * (j - a[i]) + b[i] * (sum[i - 1] - (j - a[i])));
            if (j >= b[i] && dp[i - 1][j - b[i]] != inf)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - b[i]] + b[i] * (j - b[i]) + a[i] * (sum[i - 1] - (j - b[i])));
        }
    }
    int res = inf;
    for (int j = 1099; j >= 0; j--) {
        // if (dp[n][j] != inf)
        // {
        //     cout << j << ' ';
        //     cout << dp[n][j] / 2 << '\n';
        // }
        if (dp[n][j] != inf) res = min(res, dp[n][j]);
    }
    cout << 2 * res + ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        Echo2();
}
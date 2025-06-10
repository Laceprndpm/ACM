#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = 1e9;

void solve()
{
    int n, k, x;
    cin >> n >> k >> x;
    // dp[i][j] 表示第i个数，已经用掉了j次不能dp
    vector<vector<i64>> dp(n + 1, vector<i64>(k + 1));
    i64                 ans = INT32_MIN;
    for (int i = 1; i <= n; i++) {
        i64 cur;
        cin >> cur;
        dp[i][0] = max({dp[i - 1][0] + cur - x, cur - x, 0ll});
        for (int j = max(n - i - k, 1); j <= min(i, k); j++) {
            dp[i][j] = max({dp[i - 1][j - 1] + cur + x, cur + x, 0ll});
            if (j < i) dp[i][j] = max(max(0ll, dp[i - 1][j]) - x + cur, dp[i][j]);
        }
        ans = max(ans, dp[i][j]);
    }
    cout << ans << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
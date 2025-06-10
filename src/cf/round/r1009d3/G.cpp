#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 *@ Spell : dp
 */
void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<vector<i64>> dp(n, vector<i64>(n));
    for (int len = 3; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            for (int i = l + 1; i <= r - 1; i++) {
                dp[l][r] = max<i64>({dp[l][r], dp[l + 1][i - 1] + dp[i + 1][r - 1] + arr[i] * arr[l] * arr[r],
                                     dp[l][i] + dp[i + 1][r]});
            }
            dp[l][r] = max(dp[l][r], dp[l + 1][r]);
        }
    }
    cout << dp[0][n - 1] << '\n';
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
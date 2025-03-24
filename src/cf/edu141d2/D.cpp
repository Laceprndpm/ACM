#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;
constexpr int MOD = 998244353;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 1 1 1 1
    // 0 1 2 1| 2 1 0 1
    // 0 -1 0 3| 2
    //
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int                 zero = 100000;
    vector<vector<int>> dp(2, vector<int>(2 * zero));
    fill(dp[0].begin(), dp[0].end(), 0);
    dp[0][arr[2] + zero] = 1;
    for (int i = 3; i <= n; i++) {
        for (int j = 0; j <= 2 * zero - 1; j++) {
            if (j == zero) {
                dp[1][arr[i] + zero] += dp[0][j];
                dp[1][arr[i] + zero] %= MOD;
                continue;
            }
            if (arr[i] + j <= 2 * zero - 1 && arr[i] + j >= 0) {
                dp[1][arr[i] + j] += dp[0][j];
                dp[1][arr[i] + j] %= MOD;
            }
            if (arr[i] + 2 * zero - j >= 0 && arr[i] + 2 * zero - j <= 2 * zero - 1) {
                dp[1][arr[i] + 2 * zero - j] += dp[0][j];
                dp[1][arr[i] + 2 * zero - j] %= MOD;
            }
        }
        swap(dp[0], dp[1]);
        fill(dp[1].begin(), dp[1].end(), 0);
    }
    i64 ans = 0;
    for (int i = 0; i <= 2 * zero - 1; i++) {
        ans += dp[0][i];
        ans %= MOD;
    }
    cout << ans << '\n';
    return 0;
}
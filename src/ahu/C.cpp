#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int MOD = 1e9 + 7;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int d, t, m;
    cin >> d >> t >> m;
    // dp[i]，i位置有多少种方案
    vector<vector<i64>> dp(2, vector<i64>(d + m + 5));
    dp[0][d] = 1;
    for (int j = 1; j <= t; j++) {
        for (int i = 1; i <= d + m; i++) {
            dp[1][i - 1] += dp[0][i];
            dp[1][i + 1] += dp[0][i];
            dp[1][i - 1] %= MOD;
            dp[1][i + 1] %= MOD;
        }
        swap(dp[1], dp[0]);
        dp[1].assign(d + m + 5, 0);
    }
    cout << dp[0][d + 2 * m - t];
    return 0;
}
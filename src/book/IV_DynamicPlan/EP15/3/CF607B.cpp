#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> inputArr(n);
    for (int i = 0; i < n; i++) {
        cin >> inputArr[i];
    }
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    for (int t = 1; t < n; t++) {
        for (int i = 0; i < n - t; i++) {
            int j = i + t;
            if (inputArr[i] == inputArr[j]) {
                if (i + 1 >= j - 1) {
                    dp[i][j] = 1;
                }
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
            }
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }
    cout << dp[0][n - 1];
    return 0;
}
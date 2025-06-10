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
    vector<int> oriInput(n);
    for (int i = 0; i < n; i++) {
        cin >> oriInput[i];
    }
    vector<int> arr(n * 2);
    for (int i = 0; i < 2 * n; i++) {
        arr[i] = oriInput[i % n];
    }
    vector<int> prefix(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    vector<vector<int>> dp(2 * n, vector<int>(2 * n, INF));
    vector<vector<int>> dpM(2 * n, vector<int>(2 * n, 0));
    for (int i = 0; i < 2 * n; i++) {
        dp[i][i] = 0;
    }
    for (int t = 1; t < n; t++) {
        for (int i = 0; i < 2 * n - t; i++) {
            int j = i + t;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][k] + dp[k + 1][j] + prefix[j + 1] - prefix[i], dp[i][j]);
            }
        }
    }
    for (int t = 1; t < n; t++) {
        for (int i = 0; i < 2 * n - t; i++) {
            int j = i + t;
            for (int k = i; k < j; k++) {
                dpM[i][j] = max(dpM[i][k] + dpM[k + 1][j] + prefix[j + 1] - prefix[i], dpM[i][j]);
            }
        }
    }
    int ans  = INF;
    int ansM = 0;
    for (int i = 0, j = n - 1; j < 2 * n; i++, j++) {
        ans  = min(ans, dp[i][j]);
        ansM = max(ansM, dpM[i][j]);
    }
    cout << ans << '\n';
    cout << ansM << '\n';
    return 0;
}
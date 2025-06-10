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
    int    n;
    string s;
    cin >> s;
    n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        dp[i][i + 1] = s[i] != s[i + 1];
    }
    for (int t = 2; t < n; t++) {
        for (int i = 0; i < n - t; i++) {
            int j    = t + i;
            dp[i][j] = min(dp[i + 1][j] + 1, dp[i][j - 1] + 1);
            if (s[i] == s[j]) {
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
            }
        }
    }
    cout << dp[0][n - 1];
    return 0;
}
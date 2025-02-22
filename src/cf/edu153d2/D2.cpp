#include <bits/stdc++.h>
using namespace std;
using i64       = long long;
using PII       = pair<int, int>;
constexpr int N = 105;
int           n;
int           dp[2][N][N * N];

// jiangly
// 01 11

void solve()
{
    string s;
    cin >> s;
    n = s.size();
    vector<vector<int>> dp(n, vector<int>(n * n + 1));
    vector<vector<int>> ndp(n, vector<int>(n * n + 1));
    int                 need = (n * (n - 1) / 2 - c0 * (c0 - 1) / 2 + c1 * (c1 - 1) / 2) / 2;

    // dp[j][k]表示考虑前i个数字，有j个1，01+11 == k时
    dp[0][0]  = 0;
    ndp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j >= 0; j--) {
            for (int k = n * n; k >= 0; k--) {
                dp[j + 1][k + i] = min(dp[j + 1][k + i], dp[j][k]);
            }
        }
    }
    cout <<
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}

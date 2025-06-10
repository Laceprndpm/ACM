#include <bits/stdc++.h>
using namespace std;
using i64           = long long;
using PII           = pair<int, int>;
constexpr int INF   = 1e9;
const int     val[] = {1, 10, 100, 1000, 10000};

void solve()
{
    string input;
    cin >> input;
    int n = input.size();
    input += "_";
    reverse(input.begin(), input.end());
    vector<array<array<int, 2>, 5>> dp(input.size());
    for (auto& i : dp) {
        for (auto& j : i) {
            for (int& k : j) {
                k = -INF;
            }
        }
    }

    for (int j = 0; j < 5; j++) {
        dp[0][j][0] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int cur = input[i] - 'A';
        for (int j = 0; j < 5; j++) {
            int maxCurrentValue = max(cur, j);
            dp[i][maxCurrentValue][0] =
                max(dp[i - 1][j][0] + (val[cur] * (cur >= maxCurrentValue ? 1 : -1)), dp[i][maxCurrentValue][0]);
            dp[i][maxCurrentValue][1] =
                max(dp[i - 1][j][1] + (val[cur] * (cur >= maxCurrentValue ? 1 : -1)), dp[i][maxCurrentValue][1]);
            for (int k = 0; k < 5; k++) {
                int maxChangeValue = max(j, k);
                dp[i][maxChangeValue][1] =
                    max(dp[i - 1][j][0] + (val[k] * (k >= maxChangeValue ? 1 : -1)), dp[i][maxChangeValue][1]);
            }
        }
    }
    int ans = INT32_MIN;
    for (int i = 0; i < 5; i++) {
        ans = max(dp[n][i][1], ans);
    }
    cout << ans << '\n';
}

// 可以统计每个元素的前缀和数量
// 从前往后遍历
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

// A: 1 2 3 4 5 6
// B: 1 2 3 4 5 6
// Aoff = 1
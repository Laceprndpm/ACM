#include <bits/stdc++.h>
using namespace std;
using li      = long long;
const int N   = 222222;
const int K   = 22;
const li  INF = 1e18;

int n, k, x;
int a[N];
li  dp[N][K][3];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k >> x;
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= k; ++j) {
                for (int t = 0; t < 3; ++t) {
                    dp[i][j][t] = -INF;
                }
            }
        }
        dp[0][0][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                for (int t = 0; t < 3; ++t) {  // 枚举前状态
                    if (dp[i][j][t] == -INF) continue;
                    for (int jj = j; jj <= min(k, j + 1); ++jj) {  // jj = j or j+1
                        li add = a[i] + (j == jj ? -x : x);
                        for (int tt = t; tt < 3; ++tt) {  // 枚举状态
                            dp[i + 1][jj][tt] = max(dp[i + 1][jj][tt], dp[i][j][t] + (tt == 1 ? add : 0));
                        }
                    }
                }
            }
        }
        cout << max(dp[n][k][1], dp[n][k][2]) << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const int         N = 1e6 + 7;
typedef long long ll;
ll                dp[N][21], A[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        ll n, k, x;
        cin >> n >> k >> x;
        for (int i = 1; i <= n; i++) {
            cin >> A[i];
            for (int j = 0; j <= k; j++) {
                dp[i][j] = 0;
            }
        }
        ll ans = -0;
        for (ll i = 1; i <= n; i++) {
            for (int j = max(k - n + i, 0ll); j <= min(i, k); j++) {
                if (j == 0) {
                    dp[i][0] = max(A[i] - x, A[i] - x + dp[i - 1][0]);
                } else {
                    dp[i][j] = max(dp[i - 1][j - 1], 0ll) + A[i] + x;
                    if (j < i) dp[i][j] = max(max(0ll, dp[i - 1][j]) - x + A[i], dp[i][j]);
                }
                ans = max(ans, dp[i][j]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

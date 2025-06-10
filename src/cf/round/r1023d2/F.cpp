#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e16;

void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<i64> dp(n + 1, INF);
    dp[n] = 0;
    for (i64 i = n - 1; i >= 0; i--) {
        i64 p = i;
        for (int i_p = i; i_p < n; i_p++) {
            if (arr[i_p] <= arr[p]) {
                p = i_p;
            }
        }
        for (i64 j = p; j < n; j++) {
            dp[i] = min<i64>(dp[i], dp[j + 1] + j - p + 1LL * (j - i + 1) * arr[p] + (j - i));
        }
    }
    cout << dp[0] << '\n';

    // vector<int> prefixMin(n + 1);
    // vector<int> wPreMin(n + 1);
    // prefixMin[0] = INF;
    // for (int i = 0; i < n; i++) {
    //     prefixMin[i + 1] = min(prefixMin[i], arr[i]);
    //     wPreMin[i + 1]   = min(prefixMin[i], arr[i] - i);
    // }
    // int last = INF;
    // i64 ans  = 0;
    // for (int i = n - 1; i >= 0; i--) {
    //     int chose = min<i64>({arr[i], wPreMin[i + 1] + i, last + 1});
    //     ans += chose;
    //     last = chose;
    // }
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
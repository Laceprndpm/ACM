#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    i64 x;
    cin >> n >> x;
    vector<i64> dp(n + 1, -INF);
    dp[0] = 0;
    vector<i64> arr(n);
    vector<i64> prefix(n + 1);

    for (i64& i : arr) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            dp[i] = max(prefix[j + i] - prefix[j], dp[i]);
        }
    }
    for (i64 i = 0; i <= n; i++) {
        i64 ans = 0;
        for (i64 j = 0; j <= n; j++) {
            ans = max(dp[j] + min(i, j) * x, ans);
        }
        cout << ans << ' ';
    }
    cout << '\n';
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
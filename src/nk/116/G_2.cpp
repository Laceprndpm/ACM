#include <iostream>
#include <utility>
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
    int           n;
    constexpr i64 MOD = 1E9 + 7;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 c, m, k, t;
    cin >> c >> m >> k >> t;
    k %= m;
    vector<i64> dp1(m), dp2(m);
    dp1[0] = 1;
    for (int i = 0; i < n; i++) {
        arr[i] %= m;
        for (int j = m - 1; j >= 0; j--) {
            dp2[(j + arr[i]) % m] = (dp1[j] + dp1[(j + arr[i]) % m]) % MOD;
        }
        dp1 = dp2;
    }
    dp1[0]--;
    dp1[0] += MOD;
    dp1[0] %= MOD;
    vector<i64> cdp(m), ndp(m);
    cdp[c % m] = 1;
    for (int i = t; i; i >>= 1) {
        if (i & 1) {
            for (int j = 0; j < m; j++) {
                for (int jj = 0; jj < m; jj++) {
                    ndp[(j * jj) % m] = ((cdp[j] * dp1[jj] % MOD) + ndp[(j * jj) % m]) % MOD;
                }
            }
            swap(cdp, ndp);
            ndp.assign(ndp.size(), 0);
        }
        vector<i64> dp2(m);
        for (int jj = m - 1; jj >= 0; jj--) {
            for (int j = m - 1; j >= 0; j--) {
                dp2[(j * jj) % m] = ((dp1[j] * dp1[jj]) % MOD + dp2[(j * jj) % m]) % MOD;
            }
        }
        dp1 = dp2;
    }
    cout << cdp[k] % MOD << '\n';
    return 0;
}
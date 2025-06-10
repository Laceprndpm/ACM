#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e12;

void solve()
{
    i64 n;
    cin >> n;
    vector<int> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    vector<i64> cdp(2e5 + 1000), adp(2e5 + 1000, INF), bdp(2e5 + 1000, INF);
    i64         sum  = 0;
    i64         ans2 = 0;
    for (int i = 0; i < n; i++) {
        int a = arr[i], b = brr[i];
        for (int j = 0; j <= sum; j++) {
            adp[j + a] = min(adp[j + a], cdp[j] + j * a + (sum - j) * b);
            bdp[j + b] = min(bdp[j + b], cdp[j] + j * b + (sum - j) * a);
        }
        sum += a + b;
        ans2 += a * a + b * b;
        for (int j = 0; j <= 20000; j++) {
            cdp[j] = min(adp[j], bdp[j]);
            adp[j] = bdp[j] = INF;
        }
    }
    cout << *min_element(cdp.begin(), cdp.begin() + 20000) * 2 + ans2 * (n - 1) << '\n';
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
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, k;
    cin >> n >> k;
    vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<i64> b(n);
    i64         cnt = 0;
    i64         x   = -1;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++) {
        cnt += b[i] == -1;
    }
    if (cnt != n) {
        for (int i = 0; i < n; i++) {
            if (b[i] != -1) {
                x = a[i] + b[i];
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            if (b[i] != -1) {
                if (x != a[i] + b[i]) {
                    cout << 0 << '\n';
                    return;
                }
            } else {
                if (x - a[i] < 0 || x - a[i] > k) {
                    cout << 0 << '\n';
                    return;
                }
            }
        }
    }
    if (cnt == n) {
        auto [mn, mx] = minmax_element(a.begin(), a.end());
        i64 delta     = *mx - *mn;
        if (delta > k) {
            cout << 0 << '\n';
        } else {
            cout << k - delta + 1 << '\n';
        }
        return;
    }
    cout << 1 << '\n';
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
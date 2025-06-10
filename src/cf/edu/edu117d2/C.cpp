#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e9 + 50;

void solve()
{
    i64 k, x;
    cin >> k >> x;
    i64 ans;
    if (x <= (k + 1) * k / 2) {
        auto check = [&](i64 para) -> bool {
            return para * (para + 1) / 2 < x;
        };
        i64 l = 0, r = k;
        while (l <= r) {
            i64 mid = (r - l) / 2 + l;
            if (check(mid)) {
                ans = mid;
                l   = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans++;
    } else if (x <= (k + 1) * k - k) {
        x -= (k + 1) * k / 2;
        auto check = [&](i64 para) -> bool {
            return para * (k - 1 + k - para) / 2 < x;
        };
        i64 l = 0, r = k - 1;

        while (l <= r) {
            i64 mid = (r - l) / 2 + l;
            if (check(mid)) {
                ans = mid;
                l   = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ans += k;
        ans++;
    } else {
        ans = 2 * k - 1;
    }
    cout << ans << '\n';
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
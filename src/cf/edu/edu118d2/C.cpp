#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, h;
    cin >> n >> h;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    function<i64(i64)> calc = [&](i64 k) -> i64 {
        i64 res = 0;
        for (int i = 0; i < n - 1; i++) {
            res += min(arr[i + 1] - arr[i], k);
        }
        res += k;
        return res;
    };
    i64 l = 0, r = h;
    i64 ans = 0;
    while (l <= r) {
        i64 mid = (r - l) / 2 + l;
        if (calc(mid) >= h) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    return;
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
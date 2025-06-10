#include <algorithm>
#include <functional>
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
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end(), greater<>());
    vector<i64> prefix(n + 1);
    for (i64 i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    i64                 sum   = prefix[n];
    function<bool(i64)> check = [&](i64 x) -> bool {
        i64 minas = 0;
        for (i64 i = 0; i <= min(n - 1, x); i++) {
            minas = prefix[i] + arr[n - 1] - (arr[n - 1] - (x - i)) * (i + 1);
            if (sum - minas <= k) {
                return true;
            }
        }
        return false;
    };
    i64 l = 0, r = max(sum - k, 0ll);
    i64 ans = 0;
    while (l <= r) {
        i64 mid = (l + r) / 2;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
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
    // 假如操作a+b次
    // 减少了a + (prefix[b] - (b * min-a))
    // 二分操作总次数，那么log k，每次检查需要枚举b，O(n)?
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
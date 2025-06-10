#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e18;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    i64 sum = accumulate(arr.begin(), arr.end(), 0ll);
    i64 m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        i64 x, y;
        cin >> x >> y;
        i64  ans;
        auto it = lower_bound(arr.begin(), arr.end(), x);
        i64  val_Go1, val_Go2;
        if (it == arr.end()) {
            val_Go1 = *prev(it);
        } else {
            val_Go1 = *it;
        }
        if (it == arr.begin()) {
            val_Go2 = *it;
        } else {
            val_Go2 = *prev(it);
        }
        i64 ans1 = max(y - sum + val_Go1, 0ll) + max(x - val_Go1, 0ll);
        i64 ans2 = max(y - sum + val_Go2, 0ll) + max(x - val_Go2, 0ll);
        ans      = min(ans1, ans2);
        cout << ans << '\n';
    }
    return 0;
}
#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, x;
    cin >> n >> x;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    auto ptr = lower_bound(arr.begin(), arr.end(), x);
    i64  ans = arr.end() - ptr;
    while (ptr != arr.begin()) {
        auto ptr2 = ptr - 1;
        while (ptr2 != arr.begin() && *ptr2 * (ptr - ptr2) < x) {
            ptr2--;
        }
        if (*ptr2 * (ptr - ptr2) >= x) {
            ans++;
            ptr = ptr2;
        } else {
            break;
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
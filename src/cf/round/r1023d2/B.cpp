#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    auto [mn, mx] = minmax_element(arr.begin(), arr.end());
    int cnt       = count(arr.begin(), arr.end(), *mx);
    i64 res       = accumulate(arr.begin(), arr.end(), 0ll);
    if (*mx - *mn > k + 1) {
        cout << "Jerry" << '\n';
        return;
    } else if (*mx - *mn == k + 1 && cnt > 1) {
        cout << "Jerry" << '\n';
        return;
    }
    if (res % 2 == 1) {
        cout << "Tom\n";
    } else {
        cout << "Jerry" << '\n';
    }
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
#include <algorithm>
#include <cstdint>
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
    vector<i64> arr(n + 1);
    i64         sumabs = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    i64 mnP_max_insert = INT64_MAX;
    i64 mnP_min_insert = INT64_MAX;
    for (int i = 1; i < n; i++) {
        sumabs += abs(arr[i + 1] - arr[i]);
        mnP_max_insert = min(mnP_max_insert, abs(x - arr[i + 1]) + abs(x - arr[i]) - abs(arr[i + 1] - arr[i]));
        mnP_min_insert = min(mnP_min_insert, abs(1 - arr[i + 1]) + abs(1 - arr[i]) - abs(arr[i + 1] - arr[i]));
    }
    mnP_max_insert      = min({mnP_max_insert, abs(x - arr[1]), abs(1 - arr[1])});
    mnP_max_insert      = min({mnP_max_insert, abs(x - arr[n]), abs(1 - arr[n])});
    auto&& [minA, maxA] = minmax_element(arr.begin() + 1, arr.begin() + 1 + n);
    if (*minA == 1) {
        mnP_min_insert = 0;
    }
    if (*maxA >= x) {
        mnP_max_insert = 0;
    }
    i64 ans = sumabs + mnP_max_insert + mnP_min_insert;
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
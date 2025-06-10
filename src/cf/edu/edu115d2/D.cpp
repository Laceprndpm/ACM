#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
    }
    vector<i64> l(n + 1), r(n + 1);
    for (int i = 0; i < n; i++) {
        l[arr[i].first]++, r[arr[i].second]++;
    }
    i64 ans = n * (n - 1) * (n - 2) / 6;
    for (int i = 0; i < n; i++) {
        ans -= (l[arr[i].first] - 1ll) * (r[arr[i].second] - 1ll);
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
#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n + 1);
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    i64 ans = INT32_MIN;
    for (int r = 0; r <= k; r++) {  // 删除r个最大元素，即删除2(k-r)个最小元素
        int l   = 2 * (k - r);
        i64 cur = prefix[n - r] - prefix[l];
        ans     = max(ans, cur);
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
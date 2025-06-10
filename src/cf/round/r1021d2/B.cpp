#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 ans = 0;
    sort(arr.begin(), arr.end());
    int mid = (n - k + 1) / 2;
    ans     = arr[n - mid] - arr[mid - 1] + 1;
    cout << ans << '\n';
    // } else {
    //     set<i64> mt;
    //     for (int i = 0; i <= k; i++) {
    //         i64 l = i, r = n - 1 - k + i;
    //         mt.insert(arr[(l + r) / 2]);
    //     }
    //     cout << mt.size() << '\n';
    // }
    // vector<i64> prefix(n + 1);
    // for (int i = 0; i < n; i++) {
    //     prefix[i + 1] += prefix[i] + arr[i];
    // }
    // int minF = INF;
    // i64 ans  = 0;
    // for (int i = 0; i <= k; i++) {
    //     i64 l   = i;
    //     i64 r   = n - 1 - k + i;
    //     i64 mid = (l + r) / 2;
    //     f       = (-(prefix[mid] - prefix[l]) + (mid - l) * arr[mid])
    //         + ((prefix[r + 1] - prefix[mid + 1]) - (r - mid) * arr[mid]);
    //     if (f < minF) {
    //         minF = f;
    //         ans  = arr[(l + r + 1ll) / 2] - arr[(l + r) / 2] + 1;
    //     } else if (f == minF) {
    //         ans += arr[(l + r + 1ll) / 2] - arr[(l + r) / 2] + 1;
    //     }
    // }
    // cout << ans << '\n';
    // int                 l = 0, r = n - 1 - k;
    // i64                 curpos = arr[(l + r) / 2];
    // function<void(i64)> update = [&](i64 pos) -> void {
    //     while (r < n && curpos - arr[l] >= curpos - arr[r]) {
    //         f -= pos - arr[l];
    //         f += arr[r] - pos;
    //         l++, r++;
    //     }
    // };
    // for (int i = l; i <= r; i++) {
    //     f += abs(arr[i] - curpos);
    // }
    // i64 minF = f;
    // i64 ans  = 0;
    // i64 nxtpos;
    // while (r < n - 1 && curpos <= (i64)1e9) {
    //     nxtpos = (arr[l] + arr[r + 1] + 1ll) / 2;  // 下一个将发生更新的
    //     update(nxtpos);
    //     ans += nxtpos - curpos;
    //     if (f < minF) {
    //         ans = 0;
    //         f   = minF;
    //     } else if (f > minF) {
    //         break;
    //     }
    // }
    // if (f == minF) {
    //     ans += arr[(l + r + 1ll) / 2] - curpos + 1;
    // }
    // cout << ans << '\n';
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
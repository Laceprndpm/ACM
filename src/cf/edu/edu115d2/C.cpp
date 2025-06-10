#include <iostream>
#include <map>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 res = accumulate(arr.begin(), arr.end(), 0ll);
    if (res * 2 % n != 0) {
        cout << "0\n";
        return;
    }
    res = res * 2 / n;
    map<i64, i64> cnt;
    i64           ans = 0;
    for (int i = 0; i < n; i++) {
        ans += cnt[res - arr[i]];
        cnt[arr[i]]++;
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
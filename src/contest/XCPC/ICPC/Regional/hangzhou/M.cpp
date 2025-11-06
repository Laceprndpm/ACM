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
    i64 n, k;
    cin >> n >> k;

    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    n = arr.size();
    if (n == 1) {
        cout << k << ' ' << (k + 1) * k / 2;
        return;
    }
    i64 gcdans = arr[1] - arr[0];
    for (int i = 1; i < n; i++) {
        gcdans = gcd(gcdans, arr[i] - arr[i - 1]);
    }
    i64 totalans = 0;
    i64 cnt      = 0;
    for (i64 x = 1; x <= min(gcdans - arr[0], k); x++) {
        if (gcdans % (arr[0] + x) == 0) {
            cnt++;
            totalans += x;
        }
    }
    cout << cnt << ' ' << totalans << '\n';
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
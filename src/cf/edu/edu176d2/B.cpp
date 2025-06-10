#include <algorithm>
#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    if (k == 1) {
        if (n == 2) {
            i64 ans = arr[0] + arr[1];
            cout << ans << '\n';
            return;
        }
        i64 ans = *max_element(arr.begin() + 1, arr.end() - 1);
        ans += max(arr[0], arr[n - 1]);
        ans = max(ans, arr[0] + arr[n - 1]);
        cout << ans << '\n';
        return;
    }
    sort(arr.begin(), arr.end(), greater<int>());
    i64 sum = 0;
    for (int i = 0; i <= k; i++) {
        sum += arr[i];
    }
    cout << sum << '\n';
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
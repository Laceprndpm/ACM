#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
    constexpr i64 M   = 1e8;
    i64           ans = 0;
    for (int i = 0; i < n; i++) {
        ans += arr[i] * (n - 1);
    }
    for (int i = 0; i < n; i++) {
        ans -= (arr.end() - lower_bound(arr.begin() + i + 1, arr.end(), M - arr[i])) * M;
    }
    cout << ans << '\n';
    return 0;
}
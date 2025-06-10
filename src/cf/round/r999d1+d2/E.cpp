#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> marr(m);
    for (int i = 0; i < m; i++) {
        cin >> marr[i];
        marr[i] = ~marr[i];
    }
    vector<int> ans;
    ans.reserve(n * m);
    int         bin_m = (1 << m) - 1;
    vector<int> temp(m + 1);
    vector<int> popcnt(1 << m);
    for (int i = 1; i < (1 << m); i++) {
        popcnt[i] = popcnt[i >> 1] + (i & 1);
    }
    vector<int> choose(1 << m);
    for (int j = 1; j < (1 << m); j++) {
        int u     = __builtin_ctz(j);
        choose[j] = choose[j ^ (1 << u)] | marr[u];
    }
    for (int i = 0; i < n; i++) {
        temp.assign(m + 1, 0);
        int cur = arr[i];
        for (int j = 0; j <= bin_m; j++) {
            // int chose = 0;
            // for (int k = 0; k < m; k++) {
            //     if (j >> k & 1) {
            //         chose |= marr[k];
            //     }
            // }
            temp[__builtin_ctz(j)] = max(temp[__builtin_ctz(j)], (choose[j] & cur));
        }
        int sum = 0;
        for (int i = 0; i <= m; i++) {
            temp[i] -= sum;
            sum += temp[i];
        }
        ans.insert(ans.end(), temp.begin(), temp.end());
    }
    nth_element(ans.begin(), ans.begin() + k, ans.end(), greater<>());
    i64 res = accumulate(ans.begin(), ans.begin() + k, 0ll);
    i64 sum = accumulate(arr.begin(), arr.end(), 0ll);
    cout << sum - res << '\n';
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
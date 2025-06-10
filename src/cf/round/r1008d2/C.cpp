#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    // 选择最大的作为a1，接着选择n个大数作为奇位和n-1个小数作为偶位，再选一个肯定大于最大的！
    vector<int> arr(2 * n + 1);
    for (int i = 1; i <= 2 * n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin() + 1, arr.end());
    cout << arr[2 * n] << ' ';  // 最大的a1
    i64 sum = arr[2 * n];
    for (int i = 1; i <= n - 1; i++) {
        cout << arr[i] << ' ';  // 偶位
        sum -= arr[i];
        cout << arr[i + n] << ' ';  // 奇位
        sum += arr[i + n];
    }
    sum += arr[n];
    cout << sum << ' ';
    cout << arr[n] << '\n';
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
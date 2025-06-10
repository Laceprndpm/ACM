#include <iostream>
#include <numeric>
#include <vector>
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
    i64 res = accumulate(arr.begin(), arr.end(), 0ll);
    res /= (n - 1);
    for (int i = 0; i < n; i++) {
        cout << res - arr[i] << " \n"[i == n - 1];
    }
    return 0;
}
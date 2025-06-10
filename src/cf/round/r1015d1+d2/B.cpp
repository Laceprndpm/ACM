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
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end());
    if (arr[0] == arr[1]) {
        cout << "Yes\n";
        return;
    }
    i64 cur = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] % arr[0] == 0) {
            cur = gcd(cur, arr[i]);
            if (cur == arr[0]) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
    return;
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
    // gcd(a,b,c...) <= min(a,b,c...)
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
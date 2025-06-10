#include <algorithm>
#include <iostream>
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
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    bool hasd = false;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) {
            hasd = true;
            break;
        }
    }
    if (!hasd) {
        cout << "No\n";
        return;
    }
    auto it = max_element(arr.begin(), arr.end());
    cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        if (i == it - arr.begin()) {
            cout << 1 << ' ';
        } else {
            cout << 2 << ' ';
        }
    }
    cout << '\n';
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
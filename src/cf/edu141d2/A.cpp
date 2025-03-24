#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    sort(arr.begin(), arr.end(), greater<int>());
    if (arr[0] == arr[1]) {
        for (int i = 2; i < n; i++) {
            if (arr[1] != arr[i]) {
                swap(arr[1], arr[i]);
                goto YES;
            }
        }
        cout << "NO\n";
        return;
    }
YES:
    cout << "YES\n";
    for (int& i : arr) {
        cout << i << ' ';
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
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
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> arr2(n);
    for (int i = 0; i < n; i++) {
        cin >> arr2[i];
    }
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != arr2[i]) {
            l = i;
            break;
        }
    }
    for (int i = n - 1; i > l; i--) {
        if (arr[i] != arr2[i]) {
            r = i;
            break;
        }
    }
    int minE = *min_element(arr.begin() + l, arr.begin() + r + 1);
    int maxE = *max_element(arr.begin() + l, arr.begin() + r + 1);
    while (l > 0 && arr[l - 1] <= minE) {
        minE = arr[l - 1];
        l--;
    }
    while (r < n - 1 && arr[r + 1] >= maxE) {
        maxE = arr[r + 1];
        r++;
    }
    cout << l + 1 << ' ' << r + 1 << '\n';
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
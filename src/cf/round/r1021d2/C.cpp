#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int>   arr(n);
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    sort(arr.begin(), arr.end());
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    int dp   = 0;
    int last = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] != last + 1) {
            dp = 0;
        }
        if (cnt[arr[i]] >= 4) {
            cout << "Yes\n";
            return;
        }
        if (cnt[arr[i]] >= 2 && dp) {
            cout << "Yes\n";
            return;
        }
        if (cnt[arr[i]] >= 2) {
            dp = 1;
        }
        last = arr[i];
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
    // 2 2
    // 3
    // 4 4
    //
    // 0 1
    // 1 1
    // x 0 1
    // x x 0 1
    // x x 1 1
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
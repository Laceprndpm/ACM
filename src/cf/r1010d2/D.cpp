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
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int cnt = 0;
    int l   = 0;
    int r   = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i + 1]) {
            cnt++;
            if (l == 0) {
                l = i;
            }
            r = i + 1;
        }
    }
    int ans = 0;
    if (cnt % 2 == 1) {
        ans = (cnt + 1) / 2;
    } else {
        ans = (cnt / 2) + (arr[l] + r - l > arr[r]);
    }
    cout << ans << '\n';
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
    // 1 9 1 9 8 1 0
    // -1 0 1 9 8 1 0
    //          10 9 0
    // 1 9 1 9 7 5 1
    //
    // 1 9 1 9 8 1 0
    // 1 9 5 7 8 1 0
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
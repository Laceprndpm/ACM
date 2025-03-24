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
    int n, x;
    cin >> n >> x;
    vector<i64> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin() + 1, arr.begin() + 1 + n);
    vector<i64> prefix(n + 1);
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
    i64 days = 0;
    i64 ptr  = n;
    i64 ans  = 0;
    while (ptr > 0) {
        while (ptr > 0 && (days * ptr) + prefix[ptr] > x) {
            ptr--;
        }
        if (ptr == 0) {
            break;
        }
        i64 nextdays = (x - prefix[ptr]) / ptr;
        ans += (nextdays - days + 1) * ptr;
        days = nextdays + 1;
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
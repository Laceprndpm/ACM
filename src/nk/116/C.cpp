#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    function<i64(i64, i64)> cob = [&](i64 a, i64 b) -> i64 {
        i64 res = 0;
        res     = (a & b) << 1;
        return res;
    };
    for (int i = 0; i < q; i++) {
        i64 l, r;
        cin >> l >> r;
        l--, r--;
        if (l == r) {
            cout << arr[l] << '\n';
            continue;
        }
        if (r - l >= 70) {
            cout << 0 << '\n';
            continue;
        }
        i64 res = cob(arr[l], arr[l + 1]);
        for (int i = l + 2; i <= r; i++) {
            res = cob(res, arr[i]);
        }
        cout << res << '\n';
    }
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
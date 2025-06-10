#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    // i64 ans = 0;
    // int n, x;
    // cin >> n >> x;
    // int need = n;
    // for (int i = 29; i >= 0; i--) {
    //     if (x & 1 << i) {  // if this pos has
    //         ans += 1 << i;
    //         n -= need;
    //     }
    // }
    // if (need > 0) {
    //     ans += (need + 1) / 2 * 2;
    // }
    // cout << ans << '\n';
    i64 ans = 0;
    int n, x;
    cin >> n >> x;
    if (n == 1) {
        if (x)
            cout << x << '\n';
        else
            cout << -1 << '\n';
        return;
    } else if (n == 2) {
        if (x == 1) {
            cout << 5 << '\n';
            return;
        } else if (x == 0) {
            cout << 2 << '\n';
            return;
        } else {
            for (int i = 0; i <= 30; i++) {
                if (x == (1 << i)) {
                    cout << x + 2 << '\n';
                    return;
                }
            }
            cout << x << '\n';
            return;
        }
    } else {
        int need = n;
        ans += x;
        for (int i = 30; i >= 0; i--) {
            if (x & 1 << i) {  // if this pos has
                need--;
            }
        }
        if (need > 0) {
            if (need % 2) {
                if (x != 0 && x != 1) {
                    need++;
                    ans += need;
                } else {
                    ans += need - 1 + 4;
                }
            } else {
                ans += need;
            }
        }
        cout << ans << '\n';
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
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    i64 ans  = (n / 360ll) * 900ll;
    i64 ans2 = INF;
    n %= 360ll;
    for (i64 i = 0; i <= 20; i++) {
        for (i64 j = 0; j <= 15; j++) {
            for (i64 k = 0; k <= 12; k++) {
                if (i * 6 + j * 8 + k * 10 >= n) {
                    ans2 = min<i64>(ans2, i * 15ll + j * 20ll + k * 25ll);
                }
            }
        }
    }
    cout << ans + ans2 << '\n';
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
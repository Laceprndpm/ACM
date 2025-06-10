#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, B, x, y;
    cin >> n >> B >> x >> y;
    i64 a   = 0;
    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a + x <= B) {
            a += x;
        } else {
            a -= y;
        }
        ans += a;
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
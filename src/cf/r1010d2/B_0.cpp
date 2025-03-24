#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 x, n, m;
    cin >> x >> n >> m;
    if (n >= 32) {
        cout << 0 << ' ' << 0 << '\n';
        return;
    }
    if (m >= 32) {
        m = 31;
    }
    i64 x1 = x;
    for (int i = 1; i <= n; i++) {
        x1 /= 2;
    }
    for (int i = 1; i <= m; i++) {
        x1++;
        x1 /= 2;
    }
    i64 x2 = x;
    for (int i = 1; i <= m; i++) {
        x2++;
        x2 /= 2;
    }
    for (int i = 1; i <= n; i++) {
        x2 /= 2;
    }
    cout << x2 << ' ' << x1 << '\n';
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
#include <cmath>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 x, y;
    cin >> x >> y;
    if (x == 0 && y == 0) {
        cout << 0 << '\n';
        return;
    }
    if (x == 0 || y == 0) {
        cout << 1 << '\n';
        return;
    }
    if ((i64)sqrt(x * x + y * y) * (i64)sqrt(x * x + y * y) == x * x + y * y) {
        cout << 1 << '\n';
    } else {
        cout << 2 << '\n';
    }
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
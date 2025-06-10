#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a + b + c + d == 0) {
        cout << 0 << '\n';
        return;
    } else if (a + b + c + d <= 3) {
        cout << 1 << '\n';
        return;
    } else {
        cout << 2 << '\n';
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
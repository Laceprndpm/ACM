#include <iostream>
#include <utility>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 x1, p1, x2, p2;
    cin >> x1 >> p1 >> x2 >> p2;
    int mn = min(p1, p2);
    p1 -= mn, p2 -= mn;

    if (p1 > 9) {
        cout << ">\n";
        return;
    }
    if (p2 > 9) {
        cout << "<\n";
        return;
    }
    for (int i = 0; i < p1; i++) {
        x1 *= 10;
    }
    for (int i = 0; i < p2; i++) {
        x2 *= 10;
    }
    if (x1 > x2) {
        cout << '>';
    } else if (x1 == x2) {
        cout << '=';
    } else {
        cout << '<';
    }
    cout << '\n';
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
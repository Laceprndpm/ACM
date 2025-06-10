#include <algorithm>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int w, h;
    cin >> w >> h;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    int w1, h1;
    cin >> w1 >> h1;
    if (x1 >= w1 || y1 >= h1 || x2 + w1 <= w || y2 + h1 <= h) {
        cout << 0 << '\n';
        return;
    }
    int ans = INF;
    if (w1 - x1 + x2 <= w) {
        ans = min({ans, w1 - x1, x2 - (w - w1)});
    }

    if (h1 - y1 + y2 <= h) {
        ans = min({ans, h1 - y1, y2 - (h - h1)});
    }
    if (ans == INF) {
        cout << -1 << '\n';
    } else {
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
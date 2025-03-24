#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int xA, xB, xC, yA, yB, yC;
    cin >> xA >> yA;
    cin >> xB >> yB;
    cin >> xC >> yC;
    int x1 = xB - xA, x2 = xC - xA;
    int y1 = yB - yA, y2 = yC - yA;
    int y = 0;
    if ((y1 > 0 && y2 > 0) || (y1 < 0 && y2 < 0)) {
        y = min(abs(y1) + 1, abs(y2) + 1);
    }
    int x = 0;
    if ((x1 > 0 && x2 > 0) || (x1 < 0 && x2 < 0)) {
        x = min(abs(x1) + 1, abs(x2) + 1);
    }
    if (x > 0 && y > 0) {
        cout << x + y - 1;
        cout << '\n';
        return;
    } else if (x == 0 && y == 0) {
        cout << 1 << '\n';
        return;
    } else {
        cout << x + y << '\n';
        return;
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using i64 = long long;

void solve()
{
    int k;
    cin >> k;
    vector<pair<int, int>> points;

    int rowcnt = 0;
    int currow = 0, curcol = 0;
    while (k) {
        if (k - rowcnt < 0) {
            currow++;
            rowcnt = 1;
            points.push_back({currow, curcol});
            curcol++;
        } else {
            points.push_back({currow, curcol});
            curcol++;
            k -= rowcnt;
            rowcnt++;
        }
    }
    cout << points.size() << '\n';
    for (auto [x, y] : points) {
        cout << x << ' ' << y << '\n';
    }
}

signed main()
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

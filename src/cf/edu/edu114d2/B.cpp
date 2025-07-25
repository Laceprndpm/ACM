#include <algorithm>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int a, b, c, m;
    cin >> a >> b >> c >> m;
    int up = 0;
    for (int i : {a, b, c}) {
        up += max(i - 1, 0);
    }
    int low = 0;
    low     = max(2 * max({a, b, c}) - a - b - c - 1, 0);
    if (m <= up && m >= low) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
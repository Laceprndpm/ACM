#include <algorithm>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string bs = s;
    // i = 0, j = 0, k = 1, l = x, 则可将0移到任意位
    bs.erase(unique(bs.begin(), bs.end()), bs.end());
    if (bs.size() == 1) {
        cout << 1 << '\n';
    } else if (bs.size() == 2) {
        // 1 * 1, 2 * 2
        // 1~4
        cout << 1ll + min<i64>(3, count(s.begin(), s.end(), bs[1])) << '\n';
    } else {
        cout << (count(s.begin(), s.end(), bs[0]) != 0) + (count(s.begin(), s.end(), bs[1]) != 0) << '\n';
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
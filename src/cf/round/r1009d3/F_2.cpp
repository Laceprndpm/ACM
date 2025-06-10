#include <functional>
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 * @Spell : divide and conquer
 */
void solve()
{
    i64 l1, l2, r1, r2;
    cin >> l1 >> l2 >> r1 >> r2;
    i64                   ans = (l2 - l1) * (r2 - r1);
    function<void(int k)> dfs = [&](int k) -> void {
        i64 a1 = (l1 + (1 << k) - 1) / (1 << k), a2 = l2 / (1 << k);
        i64 b1 = ((r1 + (1 << k) - 1) / (1 << k)), b2 = r2 / (1 << k);
        if (a2 >= a1 && b2 >= b1) ans -= (a2 - a1) * (b2 - b1) * 3;
        if (k < 30) dfs(k + 1);
    };
    dfs(1);
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
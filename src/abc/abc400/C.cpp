#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n;
    cin >> n;
    i64 ans = 0;
    i64 i;
    for (i = 1; i * i <= n / 2; i++) {
        if (i * i * 4 <= n) ans += 1;
        ans += 1;
        // a == 1 || a == 2
        //
        // 2 = 2 ** 1 * 1 * 1
        // 4 = 2 ** 2 * 1 * 1
        // 16 = 2 ** 0 * 2 * 2
        // 8 = 2 ** 1 * 2 * 2
    }
    cout << ans << '\n';
    return 0;
}
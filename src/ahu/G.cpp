#include <numeric>
#define REMOVE_ME
#include <iostream>
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
    int ans = 0;
    for (int i = 1; i <= 2020; i++) {
        if (gcd(i, 1018) == 1) {
            ans++;
        }
    }
    cout << ans;
    return 0;
}
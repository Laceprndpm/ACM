#include <cmath>
#include <iostream>
#define REMOVE_ME
using namespace std;
using i64         = __int128;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 curb(i64 x)
{
    i64 l = 0, r = 1e7;
    while (l < r) {
        i64 mid = (l + r + 1) / 2;
        if (mid * mid * mid <= x) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    if (l * l * l == x)
        return l;
    else
        return 0;
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
    long long N;
    cin >> N;
    for (i64 i = powl(N, 1.0 / 3.0); i <= (i64)powl(N, 1.0 / 2.0); i++) {
        i64 y = curb(i * i * i - N);
        if (y) {
            cout << (long long)i << ' ' << (long long)y << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}
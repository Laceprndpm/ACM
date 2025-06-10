#include <iostream>
#include <numeric>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

tuple<i64, i64, i64> exgcd(i64 a, i64 b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {1, 0, a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    i64 x = ly;
    i64 y = lx - ly * (a / b);
    return {x, y, r};
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
    i64 x, y, m, n, L;
    cin >> x >> y >> m >> n >> L;
    // (x + tm) % L == (y + tn) % L
    // (x - y) % L == t(n - m) % L
    // x - y == t(n - m) + z * L
    i64 lhs = x - y, w = (n - m);
    if (w < 0) {
        w   = -w;
        lhs = -lhs;
    }
    auto [a, b, r] = exgcd(L, w);
    if (lhs % r != 0) {
        cout << "Impossible" << '\n';
    } else {
        b = (b * (lhs / r) % (L / r) + (L / r)) % (L / r);
        cout << b << '\n';
    }
    return 0;
}

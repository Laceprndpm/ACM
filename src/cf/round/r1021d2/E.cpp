#include <array>
#include <iostream>
#include <numeric>
#include <span>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <class T>

tuple<T, T, T> exgcd(T a, T b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {1, 0, a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    T x = ly;
    T y = lx - ly * (a / b);
    return {x, y, r};
}

template <class T>
T CRT(int k, T* aArr, T* rArr)
{
    T M = 1, Mi = 0;
    for (int i = 0; i < k; i++) {
        M = M * rArr[i];
    }
    for (int i = 0; i < k; i++) {
        auto [a, b, r] = exgcd(M / aArr[i], rArr[i]);
        // (a * M/i) % p = 1
        while (a < 0) {
            a += aArr[i];
        }
        Mi += a * rArr[i] * M / aArr[i];
    }
    return (Mi % M + M) % M;
}

void solve()
{
    i64 n, x, y, vx, vy;
    cin >> n >> x >> y >> vx >> vy;
    // x + vx * t = 0 (mod n)
    // y + vy * t = 0 (mod n)
    //
    //
    i64 gc = gcd(vx, vy);
    vx /= gc, vy /= gc;
    array<i64, 2> a{vx, vy};
    array<i64, 2> r{x, y};
    auto          res = CRT(2, a.data(), r.data());
    cout << res << '\n';
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
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

// vectors
#define len(x)  int(x.size())
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()
#define mp      make_pair
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

// #if defined(DEBUG)
// #define SHOW(...)                                    SHOW_IMPL(__VA_ARGS__, SHOW6, SHOW5, SHOW4, SHOW3, SHOW2,
// SHOW1)(__VA_ARGS__) #define SHOW_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME #define SHOW1(x) print(#x, "=", (x)),
// flush() #define SHOW2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush() #define
// SHOW3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush() #define
// SHOW4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
// #define SHOW5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w),
// #v, "=", (v)), flush()
// #define SHOW6(x, y, z, w, v, u) \
//     print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
// #else
// #define SHOW(...)
// #endif

inline void NO()
{
    cout << -1 << '\n';
}

void case1(int n, i64 m)
{
    for (i64 k = 0; k < n; k++) {
        if ((k * (n - k) + n) * 5ll < m * 4ll) continue;
        cout << string(k, '1') + string(n - k, '0') << '\n';
        return;
    }
    // cout << __LINE__ << '\n';
    assert(0);
}

inline bool check(i64 num, i64 m)
{
    return abs(num - m) * 5 < m;
}

void case2(i64 n, i64 m)
{
    for (i64 k = 2; k <= 7; k++) {
        i64 num = (k - 1) * n * n / (2 * k);
        if (!check(num, m)) continue;
        i64 rem  = n - (k - 1) * k / 2;
        i64 each = rem / k;
        for (int i = 0; i < k; i++) {
            cout << string(each, '0');
            if (i != k - 1) {
                cout << string(i + 1, '1');
            }
        }
        //
        cout << string(rem - each * k, '0');
        cout << '\n';
        return;
    }
    // SHOW(1);
    assert(0);
}

void solve()
{
    i64 n, m;
    cin >> n >> m;
    int k = n / 2;
    if (m * 4 > n * 5 && 6 * m < (2 * n - 1) * 5) NO();
    // n < m *  0.8, m * 6 < 10 * n - 5
    else if ((m * 4 <= n * 5 || 6 * m >= 5 * (2 * n - 1)) && (5 * ((n - k) * k + n) >= 4 * m))
        case1(n, m);
    else
        case2(n, m);
    // k = (n - 1) / 2
    // k * (n - k) = n * k - k * k
    // k = (n - 1) / 2, n / 2
    // k(n − k) + n
    //
    // n, 2n - 1, 3n - 4, 4n - 9
    //
    // (2.5n - 2.5) * 0.8 = 2n - 2
    //  3n - 3
    //
    // (n - k) * k + n > 0.8 * m
    //
    // n * n / 4 / (4 / 5) = 5 / 16 = 0.3125 ~ 3 / 10
    //
    //
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
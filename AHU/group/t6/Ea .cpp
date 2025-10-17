#include <deque>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
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

namespace detail {

// 检测是否可迭代
template <class T, class = void>
struct is_iterable : std::false_type {};

template <class T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

// 递归打印
template <class T>
void smart_print(std::ostream& os, const T& val, int indent = 0)
{
    if constexpr (is_iterable<T>::value && !std::is_same_v<T, std::string>) {
        if (indent == 0) {
            os << '\n';
        }
        using element_type   = typename T::value_type;
        constexpr bool is_2d = is_iterable<element_type>::value;
        os << (is_2d ? "[\n" : "[");
        for (auto it = val.begin(); it != val.end();) {
            if constexpr (is_2d) os << std::string(indent + 2, ' ');
            smart_print(os, *it, indent + 2);
            if (++it != val.end()) os << (is_2d ? ",\n" : ", ");
        }
        os << (is_2d ? "\n" + std::string(indent, ' ') : "") << "]";
    } else {
        os << val;  // 基础类型直接输出
    }
}
}  // namespace detail

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void flush() { std::cerr.flush(); }

template <class T>
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
{
    dbg_wt(head);
    if (sizeof...(Tail)) dbg_wt(' ');
    print(forward<Tail>(tail)...);
}

#if defined(DEBUG)
#define dbg(...)                                    dbg_IMPL(__VA_ARGS__, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
#define dbg_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define dbg1(x)                                     print(#x, "=", (x)), flush()
#define dbg2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush()
#define dbg3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define dbg4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define dbg5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define dbg6(x, y, z, w, v, u) \
    print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define dbg(...)
#endif
vector<i64>   ca;
constexpr i64 MAXN = 1e12;

void maininit()
{
    deque<i64> loveme;
    loveme.pb(1);
    while (!loveme.empty()) {
        i64 i = loveme.front();
        loveme.pop_front();
        ca.pb(i);
        if (i * 2 > MAXN) continue;
        loveme.pb(i * 2);
    }
    loveme.ins(loveme.end(), all(ca));
    while (!loveme.empty()) {
        i64 i = loveme.front();
        loveme.pop_front();
        ca.pb(i);
        if (i * 5 > MAXN) continue;
        loveme.pb(i * 5);
    }
    sor(ca);
    ca.erase(unique(all(ca)), ca.end());
}

template <typename T>
T stein_gcd(T a, T b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    // a 和 b 都为偶数
    if ((a & 1) == 0 && (b & 1) == 0) return stein_gcd(a >> 1, b >> 1) << 1;

    // a 为偶数，b 为奇数
    if ((a & 1) == 0) return stein_gcd(a >> 1, b);

    // a 为奇数，b 为偶数
    if ((b & 1) == 0) return stein_gcd(a, b >> 1);

    // a 和 b 都为奇数，且 a >= b
    if (a >= b)
        return stein_gcd((a - b) >> 1, b);
    else
        return stein_gcd((b - a) >> 1, a);
}

void solve()
{
    i64 a, b;
    cin >> a >> b;
    i64 ccb = b;
    while (ccb % 2 == 0) {
        ccb /= 2;
    }
    while (ccb % 5 == 0) {
        ccb /= 5;
    }
    if (ccb == 1) {
        cout << 0 << ' ' << 1 << '\n';
        return;
    }
    pair<i64, i64> c_ica = {INF, 0};
    for (i64 ica : ca) {
        // if (b * ica > MAXN) break;
        i64 val  = a * ica;
        i64 meet = ((val - 1) / ccb + 1) * ccb;
        i64 need = meet - val;
        i64 gc   = gcd(need, ica * b);
        i64 c = need / gc, d = ica * b / gc;
        if (d > 1e9) continue;
        if (c < c_ica.fi) {
            c_ica = {c, d};
        }
    }
    // a / b + c / d
    // ad + cb / bd
    // ad = val, cb = need * b
    cout << c_ica.fi << ' ' << c_ica.se << '\n';
}

signed main(signed argc, char** argv)
{
    maininit();
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

// 4
// 1 2
// 2 3
// 3 7
// 19 79

// 11 12
// 28 53
// 17 60
// 2 35
// 17 181
// 80 123
// 68 141
// 79 163
// 71 99
// 13 64
// 33 61
// 15 32
// 16 61
// 11 86
// 33 74
// 128 143
// 40 53
// 7 23
// 30 31
// 5 6
// 86 181
// 73 91
// 13 23
// 71 81
// 1 2
// 7 38
// 117 160
// 33 83
// 129 151
// 88 153
// 25 58
// 16 19
// 19 141
// 95 124
// 43 96
// 71 139
// 11 59
// 106 109
// 93 152
// 34 43
// 17 99
// 1 57
// 20 159
// 16 25
// 5 73
// 159 170
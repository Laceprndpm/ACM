#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

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

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print()
{
    dbg_wt('\n');
}

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
constexpr i64 MOD = 1e9 + 7;

i64 qpow(i64 n, i64 q, i64 mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    auto to_Manhattan = [](pair<i64, i64> point) -> pair<i64, i64> {
        i64 tx = (point.fi + point.se) / 2;
        i64 ty = (point.fi - point.se) / 2;
        return {tx, ty};
    };

    struct Point {
        i64 x, y;
        i64 ai;
    };

    int n;

    cin >> n;
    vector<Point> points(n);

    for (int i = 0; i < n; i++) {
        i64 l, r, ai;
        cin >> l >> r >> ai;
        l *= 2, r *= 2;
        auto [x, y] = to_Manhattan({l, r});
        points[i]   = {x, y, ai};
    }
    sort(all(points), [](Point a, Point b) {
        return a.x < b.x;
    });
    vector<i64> prefix(n + 1);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        prefix[i + 1] += points[i].x;
        prefix[i + 1] %= MOD;
    }
    i64 ans_x = 0;
    for (int i = 0; i < n; i++) {
        i64 sum_x = prefix[n] - prefix[i + 1] - (n - i - 1) * points[i].x % MOD;
        sum_x += i * points[i].x % MOD - prefix[i];
        ans_x += sum_x * points[i].ai % MOD;
        ans_x %= MOD;
        ans_x += MOD;
    }
    sort(all(points), [](Point a, Point b) {
        return a.y < b.y;
    });
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        prefix[i + 1] += points[i].y;
        prefix[i + 1] %= MOD;
    }
    for (int i = 0; i < n; i++) {
        i64 sum_y = prefix[n] - prefix[i + 1] - (n - i - 1) * points[i].y % MOD;
        sum_y += i * points[i].y % MOD - prefix[i];
        ans_x += sum_y * points[i].ai % MOD;
        ans_x %= MOD;
        ans_x += MOD;
    }
    ans_x %= MOD;
    cout << ans_x * 500000004ll % MOD << '\n';
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
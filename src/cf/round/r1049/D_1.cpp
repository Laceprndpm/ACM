#include <algorithm>
#include <iostream>
#include <numeric>
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

void solve()
{
    // 感觉人话就是，给定n个pii，每个pair只能选x或者y
    // 最终使得数量相等，且sum y - sum x最大
    // 如果a左右 < b左右，则a如果右，则b一定右
    // a如果左，b未必左
    // 记为a < b
    // 如果a包含b，则可能都左，也可能都右，也可能一左一右
    // 5
    // 1 11 x
    // 2 7
    // 15 20 x
    // 1 3 x
    // 11 15 x
    //
    // 1 20 = 19
    // 1 15 = 14
    //
    // try 贪心
    //
    // 1
    // 4
    // 5 5
    // 6 8
    // 4 9
    // 5 7
    
    // {2 3} {1 4} = 6
    // {1 3} {4 2} = 7
    // a.fi <= c.fi <= d.se <= b.se
    // b.se - a.fi >= a.se - b.fi
    // b.se - d.fi >= d.se - b.fi
    // b.se + b.fi >= d.fi + d.se
    //
    //
    // 1.fi <= 3.fi <= 4.se <= 2.se
    // 2.se - 1.fi >= 1.se - 2.fi
    // c
    //
    //
    //
    // {1 2} {3 4} = 6
    // {a b} {c d} 可以反悔吗？
    // 1
    // 5
    // 3 4 7
    // 1 7 8
    // 1 7 8
    // 2 7 9
    // 8 9 17
    //
    // 3 9
    //
    //
    int n;
    cin >> n;
    vector<int> li(n);
    vector<int> ri(n);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        li[i] = l;
        ri[i] = r;
    }
    vector<int> idx1(n), idx2(n);
    iota(all(idx1), 0), iota(all(idx2), 0);
    sort(all(idx1), [&](int id1, int id2) { return li[id1] + ri[id1] < li[id2] + ri[id2]; });
    i64 ans = 0;
    for (int i = 0; i < n / 2; i++) {
        ans -= li[idx1[i]];
        ans += ri[idx1[n - 1 - i]];
    }
    if (n % 2 == 1 && n != 1) {
        int mid   = idx1[n / 2];
        int minli = -INF;
        for (int i = 0; i < n / 2; i++) {
            minli = max(minli, li[idx1[i]]);
        }
        int minri = INF;
        for (int i = 0; i < n / 2; i++) {
            minri = min(minri, ri[idx1[n - 1 - i]]);
        }
        int add1 = -li[mid] + minli;
        int add2 = ri[mid] - minri;
        ans += max({add1, add2, 0});
    }
    for (int i = 0; i < n; i++) {
        ans += ri[i] - li[i];
    }
    cout << ans << '\n';
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
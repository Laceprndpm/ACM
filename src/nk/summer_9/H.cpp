#include <algorithm>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <vector>
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
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

constexpr i64 INF = 1e16;

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
long long days_since_1970(int year, int month, int day)
{
    tm t      = {};
    t.tm_year = year - 1900;  // tm_year = 年份-1900
    t.tm_mon  = month - 1;    // tm_mon = 0~11
    t.tm_mday = day;
    time_t tt = timegm(&t);  // 转成 time_t（秒）
    if (tt == -1) return -1;

    return std::chrono::duration_cast<std::chrono::duration<long long, std::ratio<i128(86400)>>>(
               std::chrono::system_clock::from_time_t(tt) - std::chrono::system_clock::from_time_t(0))
        .count();
}

long long funcB(int year, int month, int day, int h, int m, int s)
{
    tm t      = {};
    t.tm_year = year - 1900;  // tm_year = 年份-1900
    t.tm_mon  = month - 1;    // tm_mon = 0~11
    t.tm_mday = day;
    t.tm_hour = h;
    t.tm_min  = m;
    t.tm_sec  = s;
    time_t tt = timegm(&t);  // 转成 time_t（秒）
    if (tt == -1) return -1;
    tt -= 20 * 3600;
    return std::chrono::duration_cast<std::chrono::duration<i128, std::ratio<i128(86400)>>>(
               std::chrono::system_clock::from_time_t(tt) - std::chrono::system_clock::from_time_t(0))
        .count();
}

long long funcA(int year, int month, int day, int h, int m, int s)
{
    tm t      = {};
    t.tm_year = year - 1900;  // tm_year = 年份-1900
    t.tm_mon  = month - 1;    // tm_mon = 0~11
    t.tm_mday = day;
    t.tm_hour = h;
    t.tm_min  = m;
    t.tm_sec  = s;
    time_t tt = timegm(&t);  // 转成 time_t（秒）
    if (tt == -1) return -1;
    tt += 6 * 3600;
    return std::chrono::duration_cast<std::chrono::duration<i128, std::ratio<86400>>>(
               std::chrono::system_clock::from_time_t(tt) - std::chrono::system_clock::from_time_t(0))
        .count();
}

int Mvec[] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 29};

// void solve()
// {
//     for (int year = 1970; year <= 1970; year++) {
//         for (int month = 1; month <= 12; month++) {
//             int days;
//             if (month == 2) {
//                 if ((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0)) {
//                     days = Mvec[13];
//                 } else {
//                     days = Mvec[2];
//                 }
//             } else {
//                 days = Mvec[month];
//             }
//             for (int day = 1; day <= days; day++) {
//                 cout << days_since_1970(year, month, day) << '\n';
//             }
//         }
//     }
// }

void solve()
{
    int n;
    scanf("%d", &n);
    vector<i64> days;
    for (int i = 0; i < n; i++) {
        int yy, mm, dd, h, m, s;
        // 2020-02-29 09:10:23
        scanf("%d-%d-%d %d:%d:%d", &yy, &mm, &dd, &h, &m, &s);
        i64 a = funcA(yy, mm, dd, h, m, s);
        i64 b = funcB(yy, mm, dd, h, m, s);
        for (i64 j = a; j >= b; j--) {
            days.pb(j);
        }
    }
    vector<i64> lisanhua;
    for (i64 i : days) {
        lisanhua.pb(i - 1), lisanhua.pb(i), lisanhua.pb(i + 1);
    }
    sor(lisanhua);
    lisanhua.erase(unique(all(lisanhua)), lisanhua.end());
    int num = lisanhua.size();
    for (i64& i : days) {
        i = lower_bound(all(lisanhua), i) - lisanhua.begin();
    }
    vector<i64> dp(num, 0);
    for (i64 i : days) {
        dp[i] = max(dp[i - 1] + 1, dp[i]);
    }
    i64 ans = 0;
    ans     = *max_element(all(dp));
    printf("%lld 1", ans);
}

signed main(signed argc, char** argv)
{
    freopen("./15.in", "r", stdin);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
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
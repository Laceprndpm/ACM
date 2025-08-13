#include <bits/stdc++.h>

#include <functional>
#include <iostream>
#include <queue>
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
bool isRun(int y)
{
    return (y % 4 == 0);
}

int days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int daysInMonth(int y, int m)
{
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isRun(y)) return 29;
    return days[m - 1];
}

i64 daysDiff(int y, int m, int d, int by, int bm, int bd)
{
    auto toDays = [](int y, int m, int d) {
        i64 days = 0;
        for (int year = 0; year < y; ++year)
            days += isRun(year) ? 366 : 365;
        for (int month = 1; month < m; ++month)
            days += daysInMonth(y, month);
        days += d - 1;
        return days;
    };
    return toDays(y, m, d) - toDays(by, bm, bd);
}

int weekday(int y, int m, int d)
{
    i64 diff;
    int w;
    //  1
    //  6
    //  5
    //  3
    //  2
    if (y < 2030) {
        int baseday = 2;
        diff        = daysDiff(y, m, d, 2025, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    } else if (y < 2040) {
        int baseday = 1;
        diff        = daysDiff(y, m, d, 2030, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    } else if (y < 2050) {
        int baseday = 6;
        diff        = daysDiff(y, m, d, 2040, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    } else if (y < 2060) {
        int baseday = 5;
        diff        = daysDiff(y, m, d, 2050, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    } else if (y < 2070) {
        int baseday = 3;
        diff        = daysDiff(y, m, d, 2060, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    } else {
        int baseday = 2;
        diff        = daysDiff(y, m, d, 2070, 1, 1);
        w           = (baseday + (diff % 7) + 7) % 7;
    }
    return w;
}

int already[51][13][32];

bool notFree(int y, int m, int d)
{
    if (already[y - 2025][m][d]) {
        return already[y - 2025][m][d] - 1;
    }
    if (!isRun(y) && m == 2 && d == 29) {
        already[y - 2025][m][d] = 1;
        return 0;
    }
    if (weekday(y, m, d) >= 5) {
        already[y - 2025][m][d] = 1;
        return 0;
    }
    already[y - 2025][m][d] = 2;
    return 1;
}

void solve()
{
    int k, L, R;
    cin >> k >> L >> R;
    auto work = [&](int mm, int dd) -> int {
        int val = 0;
        for (int i = L; i <= R; i++) {
            val += notFree(i, mm, dd);
        }
        return val;
    };
    vector<int> candi;
    for (int i = 0; i < 12; i++) {
        for (int j = 1; j <= days[i]; j++) {
            candi.pb(work(i + 1, j));
        }
    }
    sort(all(candi), less<>());
    i64 ans = 0;
    for (int i = 0; i < k; i++) {
        ans += candi[i];
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
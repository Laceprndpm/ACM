#include <cstdint>
#include <iostream>
#include <vector>

#ifndef DEBUG
#define NDEBUG
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
    u32 n, y, M;
    cin >> n >> y >> M;
    vector<u32>         len_vec(n);
    vector<vector<u32>> vec(n);
    for (u32 i = 0; i < n; i++) {
        cin >> len_vec[i];
        vector<u32> tmp(len_vec[i]);
        for (u32 j = 0; j < len_vec[i]; j++) {
            cin >> tmp[j];
        }
        vec[i] = tmp;
    }
    for (u32 i = 0; i < n; i++) {
        reverse(all(vec[i]));
    }
    auto check = [&](u64 s) -> int {
        for (u32 i = 0; i < n; i++) {
            u64 tmp   = 0;
            u64 cur_s = 1;
            if (s == UINT64_MAX) {
                if (len_vec[i] == 1) {
                    s = vec[i][0];
                }
                continue;
            }
            for (u32 j = 0; j < len_vec[i]; j++) {
                if (vec[i][j] >= s) {
                    return -1;
                }
            }
            for (u32 j = 0; j < len_vec[i]; j++) {
                tmp += cur_s * vec[i][j];
                if ((cur_s * s > (1e9 + 5) && j != len_vec[i] - 1) || tmp > 1e9) {
                    tmp = UINT64_MAX;
                    break;
                }
                cur_s *= s;
            }
            s = tmp;
        }
        if (s < y) {
            return -1;
        } else if (s == y) {
            return 0;
        } else {
            return 1;
        }
    };
    if (check(2) == 1 || check(M) == -1) {
        cout << "-1 -1\n";
        return;
    }
    u32 lval = 2, rval = 1e9 + 5;
    u32 lower;
    while (lval <= rval) {
        u32 mid = (rval - lval) / 2 + lval;
        if (check(mid) >= 0) {
            rval  = mid - 1;
            lower = mid;
        } else {
            lval = mid + 1;
        }
    }
    u32 higher;
    lval = 2, rval = 1e9 + 5;
    while (lval <= rval) {
        u32 mid = (rval - lval) / 2 + lval;
        if (check(mid) <= 0) {
            lval   = mid + 1;
            higher = mid;
        } else {
            rval = mid - 1;
        }
    }
    higher = min(higher, M);
    if (higher < lower) {
        cout << "-1 -1\n";
        return;
    }
    cout << lower << ' ' << higher << '\n';
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
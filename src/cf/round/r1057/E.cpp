#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
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
struct Prime {
    vector<int> minp, primes;
    vector<int> cnt;

    Prime(int n)
    {
        sieve(n);
        reverse(all(primes));
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();
        cnt.resize(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                cnt[i]  = 1;
                primes.push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                cnt[i * p]  = 1;
                if (p == minp[i]) {
                    cnt[i * p] = cnt[i] + 1;
                    break;
                }
            }
        }
    }
} prime(1e7 + 1);

void solve()
{
    // 可以肯定，一定是p^i
    // 1e7，是不是让我预处理质数？ 664579
    // min(a, b) != min(c, d)
    // m >= n，感觉很关键
    // 哪些是0，如果n! = p1^a1 * p2^a2...
    // 可以构造p1^a1,p2^a2...让v(n!) = 1感觉很难，方向不对
    // 如果只考虑n，小于n的最大的质数设为p
    // 则1...p - 1的x!都是0
    // 153
    //
    // i64 ans = 0;
    // for (int n = 1; n <= 1e7; n++) {
    // ans = max(ans, ll(n) - *lower_bound(all(pprime.primes), n, greater<>()));
    // cout << ans << '\n';
    // 对153个做暴力吗?
    // 我一定会选择什么？n的约数吗？
    // 选p，则一定会1 = 1
    // 枚举m内的？
    // m | n?
    // 如何求v_k(n!) ?
    // 1e7 * 664579有点夸张
    // 如果k是合数，那么v_k = min(v_p1 , v_p2)
    // 如果是质数，则考虑该质数的次数，只需要考虑有多少个1次方，二次方。。。log级别
    //
    int n, m;
    cin >> n >> m;
    int         p0 = *lower_bound(all(prime.primes), n, greater<>());
    vector<int> candidate;
    for (int p = p0; p <= n; p++) {
        int vp = p;
        while (vp != 1) {
            candidate.pb(prime.minp[vp]);
            vp /= prime.minp[vp];
        }
    }
    sor(candidate);
    candidate.erase(unique(all(candidate)), candidate.end());

    auto fx = [&](int x, int p) -> i64 {
        i64 c = 0;
        while (x) {
            x /= p;
            c += x;
        }
        return c;
    };
    i64 ans = 0;
    for (int i = p0; i < n; i++) {
        i64 tmpans = INF;
        for (int p : candidate) {
            i64 valx = fx(i, p);
            i64 valn = fx(n, p);
            i64 vp   = p;
            int pow  = 1;
            while (vp <= m) {
                if (valx / pow != valn / pow) {
                    tmpans = min(tmpans, valx / pow);
                }
                vp *= p;
                pow++;
            }
        }
        ans += tmpans;
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
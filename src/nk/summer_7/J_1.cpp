#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <stacktrace>
#include <vector>

#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)

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

struct Prime {
    vector<int> minp;
    vector<int> primes;

    Prime(int n)
    {
        sieve(n);
    }

    void sieve(int n)
    {
        minp.assign(n + 1, 0);
        primes.clear();

        for (int i = 2; i <= n; i++) {
            if (minp[i] == 0) {
                minp[i] = i;
                primes.push_back(i);
            }

            for (auto p : primes) {
                if (i * p > n) {
                    break;
                }
                minp[i * p] = p;
                if (p == minp[i]) {
                    break;
                }
            }
        }
    }
} prime(1e5 + 1);

constexpr i64 MOD = 998244353;

i64 qpow(i64 n, i64 q, i64 mod = MOD)
{
    if (q > MOD - 1) {
        q %= MOD - 1;
    }
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    n %= MOD;
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

template <class T>
tuple<T, T, T> exgcd(T a, T b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {T(1), T(0), a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    T x = ly;
    T y = lx - ly * (a / b);
    return {x, y, r};
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

using i128 = __int128;

istream& operator>>(istream& in, i128& num)
{
    string s;
    in >> s;
    num      = 0;
    bool neg = (s[0] == '-');
    for (size_t i = neg; i < s.size(); ++i) {
        num = num * 10 + (s[i] - '0');
    }
    if (neg) num = -num;
    return in;
}

ostream& operator<<(ostream& out, const i128& num)
{
    if (num == 0) {
        return out << '0';
    }
    i128 temp = num;
    if (temp < 0) {
        out << '-';
        temp = -temp;
    }
    string result;
    while (temp > 0) {
        result += char('0' + temp % 10);
        temp /= 10;
    }
    reverse(result.begin(), result.end());
    return out << result;
}

void solve()
{
    // 78498个质数
    i64 a, b, c, d;
    cin >> a >> b >> c >> d;
    // 如果先用1e6范围判断，则
    // 筛出的，需要逐个判断
    // 若没有筛出，则ab内若存有质数，大小>1e6，则gcd(a, b)、gcd(a * a, b)、gcd(a, b * b)就可以
    //
    i64 ans     = 1;
    i64 gcd_a_c = get<2>(exgcd(a, c));

    for (i64 i : prime.primes) {
        if (gcd_a_c % i == 0) {
            int cnt_a = 0, cnt_c = 0;
            while (a % i == 0) {
                a /= i;
                cnt_a++;
            }
            while (c % i == 0) {
                c /= i;
                cnt_c++;
            }
            ans = ans * qpow(i * 1ll, min(cnt_a * b, cnt_c * d)) % MOD;
            while (gcd_a_c % i == 0) {
                gcd_a_c /= i;
            }
        }
    }
    assert(gcd_a_c == 1 || gcd_a_c > 5e4);

    auto check2pow = [&](i64 x) -> optional<i64> {
        i64 res = sqrtl(x);

        for (i64 i = -2; i <= 2; i++) {
            if ((res + i) * (res + i) == x) return res + i;
        }
        return nullopt;
    };
    auto check3pow = [&](i64 x) -> optional<i64> {
        i64 l = 1, r = 1e6;
        i64 res = -1;
        while (l <= r) {
            i64 mid = (r - l) / 2 + l;
            if (mid * mid * mid > x) {
                r = mid - 1;
            } else {
                res = mid;
                l   = mid + 1;
            }
        }
        if (i64(res) * res * res == x) {
            return res;
        } else {
            return nullopt;
        }
    };
    if (gcd_a_c != 1) {
        auto res1 = check2pow(gcd_a_c);
        if (res1.has_value()) {  // **2
            i64 val    = res1.value();
            i64 tmpval = val;
            i64 tmpb;
            i64 tmpd;
            if (a % (tmpval * tmpval * tmpval) == 0) {
                tmpb = 3 * b;
            } else {
                tmpb = 2 * b;
            }
            if (c % (tmpval * tmpval * tmpval) == 0) {
                tmpd = 3 * d;
            } else {
                tmpd = 2 * d;
            }
            ans = ans * qpow(val, min(tmpb, tmpd)) % MOD;
        } else {
            auto res2 = check3pow(gcd_a_c);
            if (res2.has_value()) {
                i64 val = res2.value();
                ans     = ans * qpow(val, 3 * min(b, d)) % MOD;
            } else {
                i128 gcd_3 = i128(gcd_a_c) * gcd_a_c * gcd_a_c;
                if (a % gcd_3 == 0) {
                    ans = ans * qpow(gcd_a_c, min(3 * b, d)) % MOD;
                } else if (c % gcd_3 == 0) {
                    ans = ans * qpow(gcd_a_c, min(b, 3 * d)) % MOD;
                } else {
                    i64 a1 = (__gcd(i128(gcd_a_c) * gcd_a_c, i128(a)));
                    i64 c1 = (__gcd(i128(gcd_a_c) * gcd_a_c, i128(c)));
                    if (a1 / gcd_a_c != 1) {
                        i64 p1   = a1 / gcd_a_c;
                        ans      = ans * qpow(p1, min((b) * 2, (d))) % MOD;
                        i64 p2   = gcd_a_c / p1;
                        i64 tmpd = d;
                        if (c1 % (p2 * p2) == 0) {
                            tmpd *= 2;
                        }
                        ans = ans * qpow(p2, min((b), tmpd)) % MOD;
                    } else if (c1 / gcd_a_c != 1) {
                        i64 p1 = c1 / gcd_a_c;
                        ans    = ans * qpow(p1, min((b), (d) * 2)) % MOD;
                        i64 p2 = gcd_a_c / p1;
                        ans    = ans * qpow(p2, min(b, (d))) % MOD;
                    } else {
                        ans = ans * qpow(gcd_a_c, min(b, d)) % MOD;
                    }
                }
            }
        }
    }
    cout << ans % MOD << '\n';
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
// BEGIN: main.cpp
#line 1 "main.cpp"
// BEGIN: my_template.hpp
#line 1 "my_template.hpp"
#if defined(LOCAL)
#include <my_template_compiled.hpp>
#else

// https://codeforces.com/blog/entry/96344
// https://codeforces.com/blog/entry/126772?#comment-1154880
#include <bits/allocator.h>
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'010'000'000;
template <>
constexpr ll infty<ll> = 2'020'000'000'000'000'000;
template <>
constexpr u32 infty<u32> = infty<int>;
template <>
constexpr u64 infty<u64> = infty<ll>;
template <>
constexpr i128 infty<i128> = i128(infty<ll>) * 2'000'000'000'000'000'000;
template <>
constexpr double infty<double> = infty<ll>;
template <>
constexpr long double infty<long double> = infty<ll>;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;
template <class T>
using vvvc = vector<vvc<T>>;
template <class T>
using vvvvc = vector<vvvc<T>>;
template <class T>
using vvvvvc = vector<vvvvc<T>>;
template <class T>
using pq_max = priority_queue<T>;
template <class T>
using pq_min = priority_queue<T, vector<T>, greater<T>>;

#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))
#define vvv(type, name, h, w, ...) \
    vector<vector<vector<type>>> name(h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))
#define vvvv(type, name, a, b, c, ...)         \
    vector<vector<vector<vector<type>>>> name( \
        a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))

// https://trap.jp/post/1224/
#define FOR1(a)                       for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a)                    for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b)                 for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c)              for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a)                     for (ll i = (a) - 1; i >= ll(0); --i)
#define FOR2_R(i, a)                  for (ll i = (a) - 1; i >= ll(0); --i)
#define FOR3_R(i, a, b)               for (ll i = (b) - 1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif   else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define stoi stoll

int popcnt(int x)
{
    return __builtin_popcount(x);
}

int popcnt(u32 x)
{
    return __builtin_popcount(x);
}

int popcnt(ll x)
{
    return __builtin_popcountll(x);
}

int popcnt(u64 x)
{
    return __builtin_popcountll(x);
}

int popcnt_sgn(int x)
{
    return (__builtin_parity(unsigned(x)) & 1 ? -1 : 1);
}

int popcnt_sgn(u32 x)
{
    return (__builtin_parity(x) & 1 ? -1 : 1);
}

int popcnt_sgn(ll x)
{
    return (__builtin_parityll(x) & 1 ? -1 : 1);
}

int popcnt_sgn(u64 x)
{
    return (__builtin_parityll(x) & 1 ? -1 : 1);
}

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int topbit(int x)
{
    return (x == 0 ? -1 : 31 - __builtin_clz(x));
}

int topbit(u32 x)
{
    return (x == 0 ? -1 : 31 - __builtin_clz(x));
}

int topbit(ll x)
{
    return (x == 0 ? -1 : 63 - __builtin_clzll(x));
}

int topbit(u64 x)
{
    return (x == 0 ? -1 : 63 - __builtin_clzll(x));
}

// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int lowbit(int x)
{
    return (x == 0 ? -1 : __builtin_ctz(x));
}

int lowbit(u32 x)
{
    return (x == 0 ? -1 : __builtin_ctz(x));
}

int lowbit(ll x)
{
    return (x == 0 ? -1 : __builtin_ctzll(x));
}

int lowbit(u64 x)
{
    return (x == 0 ? -1 : __builtin_ctzll(x));
}

template <typename T>
T kth_bit(int k)
{
    return T(1) << k;
}

template <typename T>
bool has_kth_bit(T x, int k)
{
    return x >> k & 1;
}

template <typename UINT>
struct all_bit {
    struct iter {
        UINT s;

        iter(UINT s) : s(s) {}

        int operator*() const
        {
            return lowbit(s);
        }

        iter &operator++()
        {
            s &= s - 1;
            return *this;
        }

        bool operator!=(const iter) const
        {
            return s != 0;
        }
    };

    UINT s;

    all_bit(UINT s) : s(s) {}

    iter begin() const
    {
        return iter(s);
    }

    iter end() const
    {
        return iter(0);
    }
};

template <typename UINT>
struct all_subset {
    static_assert(is_unsigned<UINT>::value);

    struct iter {
        UINT s, t;
        bool ed;

        iter(UINT s) : s(s), t(s), ed(0) {}

        int operator*() const
        {
            return s ^ t;
        }

        iter &operator++()
        {
            (t == 0 ? ed = 1 : t = (t - 1) & s);
            return *this;
        }

        bool operator!=(const iter) const
        {
            return !ed;
        }
    };

    UINT s;

    all_subset(UINT s) : s(s) {}

    iter begin() const
    {
        return iter(s);
    }

    iter end() const
    {
        return iter(0);
    }
};

template <typename T>
T floor(T a, T b)
{
    return a / b - (a % b && (a ^ b) < 0);
}

template <typename T>
T ceil(T x, T y)
{
    return floor(x + y - 1, y);
}

template <typename T>
T bmod(T x, T y)
{
    return x - y * floor(x, y);
}

template <typename T>
pair<T, T> divmod(T x, T y)
{
    T q = floor(x, y);
    return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const U &A)
{
    return std::accumulate(A.begin(), A.end(), T{});
}

#define MIN(v)    *min_element(all(v))
#define MAX(v)    *max_element(all(v))
#define LB(c, x)  distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x)  distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(deque<T> &que)
{
    T a = que.front();
    que.pop_front();
    return a;
}

template <typename T>
T POP(pq_min<T> &que)
{
    T a = que.top();
    que.pop();
    return a;
}

template <typename T>
T POP(pq_max<T> &que)
{
    T a = que.top();
    que.pop();
    return a;
}

template <typename T>
T POP(vc<T> &que)
{
    T a = que.back();
    que.pop_back();
    return a;
}

template <typename F>
ll binary_search(F check, ll ok, ll ng, bool check_ok = true)
{
    if (check_ok) assert(check(ok));
    while (abs(ok - ng) > 1) {
        auto x               = (ng + ok) / 2;
        (check(x) ? ok : ng) = x;
    }
    return ok;
}

template <typename F>
double binary_search_real(F check, double ok, double ng, int iter = 100)
{
    FOR(iter)
    {
        double x             = (ok + ng) / 2;
        (check(x) ? ok : ng) = x;
    }
    return (ok + ng) / 2;
}

template <class T, class S>
inline bool chmax(T &a, const S &b)
{
    return (a < b ? a = b, 1 : 0);
}

template <class T, class S>
inline bool chmin(T &a, const S &b)
{
    return (a > b ? a = b, 1 : 0);
}

// ? は -1
vc<int> s_to_vi(const string &S, char first_char)
{
    vc<int> A(S.size());
    FOR(i, S.size())
    {
        A[i] = (S[i] != '?' ? S[i] - first_char : -1);
    }
    return A;
}

template <typename T, typename U>
vector<T> cumsum(vector<U> &A, int off = 1)
{
    int       N = A.size();
    vector<T> B(N + 1);
    FOR(i, N)
    {
        B[i + 1] = B[i] + A[i];
    }
    if (off == 0) B.erase(B.begin());
    return B;
}

// stable sort
template <typename T>
vector<int> argsort(const vector<T> &A)
{
    vector<int> ids(len(A));
    iota(all(ids), 0);
    sort(all(ids), [&](int i, int j) {
        return (A[i] == A[j] ? i < j : A[i] < A[j]);
    });
    return ids;
}

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I)
{
    vc<T> B(len(I));
    FOR(i, len(I)) B[i] = A[I[i]];
    return B;
}

template <typename T, typename... Vectors>
void concat(vc<T> &first, const Vectors &...others)
{
    vc<T> &res = first;
    (res.insert(res.end(), others.begin(), others.end()), ...);
}
#endif
// END: my_template.hpp
#line 2 "main.cpp"
// BEGIN: other/io.hpp
#line 1 "other/io.hpp"
#define FASTIO
#include <unistd.h>

// https://judge.yosupo.jp/submission/21623
namespace fastio {
static constexpr uint32_t SZ = 1 << 17;
char                      ibuf[SZ];
char                      obuf[SZ];
char                      out[100];
// pointer of ibuf, obuf
uint32_t pil = 0, pir = 0, por = 0;

struct Pre {
    char num[10000][4];

    constexpr Pre() : num()
    {
        for (int i = 0; i < 10000; i++) {
            int n = i;
            for (int j = 3; j >= 0; j--) {
                num[i][j] = n % 10 | '0';
                n /= 10;
            }
        }
    }
} constexpr pre;

inline void load()
{
    memcpy(ibuf, ibuf + pil, pir - pil);
    pir = pir - pil + fread(ibuf + pir - pil, 1, SZ - pir + pil, stdin);
    pil = 0;
    if (pir < SZ) ibuf[pir++] = '\n';
}

inline void flush()
{
    fwrite(obuf, 1, por, stdout);
    por = 0;
}

void rd(char &c)
{
    do {
        if (pil + 1 > pir) load();
        c = ibuf[pil++];
    } while (isspace(c));
}

void rd(string &x)
{
    x.clear();
    char c;
    do {
        if (pil + 1 > pir) load();
        c = ibuf[pil++];
    } while (isspace(c));
    do {
        x += c;
        if (pil == pir) load();
        c = ibuf[pil++];
    } while (!isspace(c));
}

template <typename T>
void rd_real(T &x)
{
    string s;
    rd(s);
    x = stod(s);
}

template <typename T>
void rd_integer(T &x)
{
    if (pil + 100 > pir) load();
    char c;
    do
        c = ibuf[pil++];
    while (c < '-');
    bool minus = 0;
    if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
        if (c == '-') {
            minus = 1, c = ibuf[pil++];
        }
    }
    x = 0;
    while ('0' <= c) {
        x = x * 10 + (c & 15), c = ibuf[pil++];
    }
    if constexpr (is_signed<T>::value || is_same_v<T, i128>) {
        if (minus) x = -x;
    }
}

void rd(int &x)
{
    rd_integer(x);
}

void rd(ll &x)
{
    rd_integer(x);
}

void rd(i128 &x)
{
    rd_integer(x);
}

void rd(u32 &x)
{
    rd_integer(x);
}

void rd(u64 &x)
{
    rd_integer(x);
}

void rd(u128 &x)
{
    rd_integer(x);
}

void rd(double &x)
{
    rd_real(x);
}

void rd(long double &x)
{
    rd_real(x);
}

void rd(f128 &x)
{
    rd_real(x);
}

template <class T, class U>
void rd(pair<T, U> &p)
{
    return rd(p.first), rd(p.second);
}

template <size_t N = 0, typename T>
void rd_tuple(T &t)
{
    if constexpr (N < std::tuple_size<T>::value) {
        auto &x = std::get<N>(t);
        rd(x);
        rd_tuple<N + 1>(t);
    }
}

template <class... T>
void rd(tuple<T...> &tpl)
{
    rd_tuple(tpl);
}

template <size_t N = 0, typename T>
void rd(array<T, N> &x)
{
    for (auto &d : x)
        rd(d);
}

template <class T>
void rd(vc<T> &x)
{
    for (auto &d : x)
        rd(d);
}

void read() {}

template <class H, class... T>
void read(H &h, T &...t)
{
    rd(h), read(t...);
}

void wt(const char c)
{
    if (por == SZ) flush();
    obuf[por++] = c;
}

void wt(const string s)
{
    for (char c : s)
        wt(c);
}

void wt(const char *s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++)
        wt(s[i]);
}

template <typename T>
void wt_integer(T x)
{
    if (por > SZ - 100) flush();
    if (x < 0) {
        obuf[por++] = '-', x = -x;
    }
    int outi;
    for (outi = 96; x >= 10000; outi -= 4) {
        memcpy(out + outi, pre.num[x % 10000], 4);
        x /= 10000;
    }
    if (x >= 1000) {
        memcpy(obuf + por, pre.num[x], 4);
        por += 4;
    } else if (x >= 100) {
        memcpy(obuf + por, pre.num[x] + 1, 3);
        por += 3;
    } else if (x >= 10) {
        int q         = (x * 103) >> 10;
        obuf[por]     = q | '0';
        obuf[por + 1] = (x - q * 10) | '0';
        por += 2;
    } else
        obuf[por++] = x | '0';
    memcpy(obuf + por, out + outi + 4, 96 - outi);
    por += 96 - outi;
}

template <typename T>
void wt_real(T x)
{
    ostringstream oss;
    oss << fixed << setprecision(15) << double(x);
    string s = oss.str();
    wt(s);
}

void wt(int x)
{
    wt_integer(x);
}

void wt(ll x)
{
    wt_integer(x);
}

void wt(i128 x)
{
    wt_integer(x);
}

void wt(u32 x)
{
    wt_integer(x);
}

void wt(u64 x)
{
    wt_integer(x);
}

void wt(u128 x)
{
    wt_integer(x);
}

void wt(double x)
{
    wt_real(x);
}

void wt(long double x)
{
    wt_real(x);
}

void wt(f128 x)
{
    wt_real(x);
}

template <class T, class U>
void wt(const pair<T, U> val)
{
    wt(val.first);
    wt(' ');
    wt(val.second);
}

template <size_t N = 0, typename T>
void wt_tuple(const T t)
{
    if constexpr (N < std::tuple_size<T>::value) {
        if constexpr (N > 0) {
            wt(' ');
        }
        const auto x = std::get<N>(t);
        wt(x);
        wt_tuple<N + 1>(t);
    }
}

template <class... T>
void wt(tuple<T...> tpl)
{
    wt_tuple(tpl);
}

template <class T, size_t S>
void wt(const array<T, S> val)
{
    auto n = val.size();
    for (size_t i = 0; i < n; i++) {
        if (i) wt(' ');
        wt(val[i]);
    }
}

template <class T>
void wt(const vector<T> val)
{
    auto n = val.size();
    for (size_t i = 0; i < n; i++) {
        if (i) wt(' ');
        wt(val[i]);
    }
}

void print()
{
    wt('\n');
}

template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail)
{
    wt(head);
    if (sizeof...(Tail)) wt(' ');
    print(forward<Tail>(tail)...);
}

// gcc expansion. called automaticall after main.
void __attribute__((destructor)) _d()
{
    flush();
}
}  // namespace fastio

using fastio::flush;
using fastio::print;
using fastio::read;

#if defined(LOCAL)
#define SHOW(...)                                    SHOW_IMPL(__VA_ARGS__, SHOW6, SHOW5, SHOW4, SHOW3, SHOW2, SHOW1)(__VA_ARGS__)
#define SHOW_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define SHOW1(x)                                     print(#x, "=", (x)), flush()
#define SHOW2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush()
#define SHOW3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define SHOW4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define SHOW5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define SHOW6(x, y, z, w, v, u) \
    print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define SHOW(...)
#endif

#define INT(...)     \
    int __VA_ARGS__; \
    read(__VA_ARGS__)
#define LL(...)     \
    ll __VA_ARGS__; \
    read(__VA_ARGS__)
#define U32(...)     \
    u32 __VA_ARGS__; \
    read(__VA_ARGS__)
#define U64(...)     \
    u64 __VA_ARGS__; \
    read(__VA_ARGS__)
#define STR(...)        \
    string __VA_ARGS__; \
    read(__VA_ARGS__)
#define CHAR(...)     \
    char __VA_ARGS__; \
    read(__VA_ARGS__)
#define DBL(...)        \
    double __VA_ARGS__; \
    read(__VA_ARGS__)

#define VEC(type, name, size) \
    vector<type> name(size);  \
    read(name)
#define VV(type, name, h, w)                       \
    vector<vector<type>> name(h, vector<type>(w)); \
    read(name)

void YES(bool t = 1)
{
    print(t ? "YES" : "NO");
}

void NO(bool t = 1)
{
    YES(!t);
}

void Yes(bool t = 1)
{
    print(t ? "Yes" : "No");
}

void No(bool t = 1)
{
    Yes(!t);
}

void yes(bool t = 1)
{
    print(t ? "yes" : "no");
}

void no(bool t = 1)
{
    yes(!t);
}

void YA(bool t = 1)
{
    print(t ? "YA" : "TIDAK");
}

void TIDAK(bool t = 1)
{
    YA(!t);
}

// END: other/io.hpp
#line 3 "main.cpp"

// BEGIN: string/substring_abundant_string.hpp
#line 1 "string/substring_abundant_string.hpp"
// BEGIN: string/run_length.hpp
#line 1 "string/run_length.hpp"

template <typename STRING = string>
vc<pair<typename STRING::value_type, ll>> run_length(STRING &S)
{
    vc<pair<typename STRING::value_type, ll>> res;
    for (auto &&x : S) {
        if (res.empty() || res.back().fi != x) {
            res.emplace_back(x, 0);
        }
        res.back().se++;
    }
    return res;
}

// END: string/run_length.hpp
#line 2 "string/substring_abundant_string.hpp"

// 部分文字列の種類数が最大であるような 01 文字列の構成
// https://qoj.ac/contest/1096/problem/5434?v=1
// https://oeis.org/A094913
// https://www.mimuw.edu.pl/~rytter/MYPAPERS/paper.pdf
string substring_abundant_string(ll N)
{
    ll N0 = N;
    N     = 1;
    while ((1 << N) + (N - 1) < N0)
        ++N;

    string S = [&]() -> string {
        if (N == 1) return "01";
        if (N == 2) return "00110";

        auto SHIFT = [&](string x, string y) -> string {
            int n = len(x);
            x += x;
            FOR(i, n, n + n)
            {
                if (x.substr(i - len(y), len(y)) == y) {
                    return x.substr(i - n, n);
                }
            }
            return "";
        };
        auto oplus = [&](string x, string y) -> string {
            int n = topbit(len(y));
            assert(len(x) == (1 << n) && len(y) == (1 << n));
            return x + SHIFT(y, x.substr(len(x) - n, n));
        };
        auto NOT = [&](string x) -> string {
            string y;
            for (auto &&s : x)
                y += (s == '0' ? '1' : '0');
            return y;
        };
        auto PSI = [&](string x) -> string {
            int a = 0;
            FOR(i, len(x))
            {
                a ^= (x[i] - '0');
                x[i] = ('0' + a);
            }
            return x;
        };

        auto NEXT = [&](string x) -> string {
            x = PSI(x);
            return oplus(x, NOT(x));
        };

        auto otimes = [&](string x, string y) -> string {
            string t;
            FOR(topbit(len(x))) t += '0';
            x = SHIFT(x, t);
            y = SHIFT(y, t);
            rotate(x.begin(), x.end() - len(t), x.end());
            rotate(y.begin(), y.end() - len(t), y.end());

            int n  = len(x);
            int x0 = 0, x1 = 0, y0 = 0, y1 = 1;
            for (auto &&[k, v] : run_length(x)) {
                if (k == '0') chmax(x0, v);
                if (k == '1') chmax(x1, v);
            }
            for (auto &&[k, v] : run_length(y)) {
                if (k == '0') chmax(y0, v);
                if (k == '1') chmax(y1, v);
            }
            string X, Y;
            for (auto &&[k, v] : run_length(x)) {
                if (k == '0' && v < x0) {
                    X += string(v, k);
                }
                if (k == '0' && v == x0) {
                    X += string(v - 1, k);
                }
                if (k == '1' && v < x1) {
                    X += string(v, k);
                }
                if (k == '1' && v == x1) {
                    X += string(v + 1, k);
                }
            }
            for (auto &&[k, v] : run_length(y)) {
                if (k == '0' && v < y0) {
                    Y += string(v, k);
                }
                if (k == '0' && v == y0) {
                    Y += string(v + 1, k);
                }
                if (k == '1' && v < y1) {
                    Y += string(v, k);
                }
                if (k == '1' && v == y1) {
                    Y += string(v - 1, k);
                }
            }
            return X + Y;
        };

        string x = "0011", y = "0011";
        FOR(i, 2, N - 1)
        {
            string t;
            FOR(i) t += '1';
            x = SHIFT(x, t);
            x = NEXT(x);
            y = SHIFT(y, t);
            y = NOT(NEXT(y));
        }
        x = otimes(x, y);
        FOR(i, N - 1) x += x[i];
        return x;
    }();
    return S.substr(0, N0);
}  // END: string/substring_abundant_string.hpp

#line 5 "main.cpp"
// BEGIN: string/suffix_array.hpp
#line 1 "string/suffix_array.hpp"

// BEGIN: alg/monoid/min.hpp
#line 1 "alg/monoid/min.hpp"

template <typename E>
struct Monoid_Min {
    using X          = E;
    using value_type = X;

    static constexpr X op(const X &x, const X &y) noexcept
    {
        return min(x, y);
    }

    static constexpr X unit()
    {
        return infty<E>;
    }

    static constexpr bool commute = true;
};

// END: alg/monoid/min.hpp
#line 4 "string/suffix_array.hpp"
// BEGIN: ds/sparse_table/sparse_table.hpp
#line 1 "ds/sparse_table/sparse_table.hpp"

// 冪等なモノイドであることを仮定。disjoint sparse table より x 倍高速
template <class Monoid>
struct Sparse_Table {
    using MX = Monoid;
    using X  = typename MX::value_type;
    int    n, log;
    vvc<X> dat;

    Sparse_Table() {}

    Sparse_Table(int n)
    {
        build(n);
    }

    template <typename F>
    Sparse_Table(int n, F f)
    {
        build(n, f);
    }

    Sparse_Table(const vc<X> &v)
    {
        build(v);
    }

    void build(int m)
    {
        build(m, [](int i) -> X {
            return MX::unit();
        });
    }

    void build(const vc<X> &v)
    {
        build(len(v), [&](int i) -> X {
            return v[i];
        });
    }

    template <typename F>
    void build(int m, F f)
    {
        n = m, log = 1;
        while ((1 << log) < n)
            ++log;
        dat.resize(log);
        dat[0].resize(n);
        FOR(i, n) dat[0][i] = f(i);

        FOR(i, log - 1)
        {
            dat[i + 1].resize(len(dat[i]) - (1 << i));
            FOR(j, len(dat[i]) - (1 << i))
            {
                dat[i + 1][j] = MX::op(dat[i][j], dat[i][j + (1 << i)]);
            }
        }
    }

    X prod(int L, int R)
    {
        if (L == R) return MX::unit();
        if (R == L + 1) return dat[0][L];
        int k = topbit(R - L - 1);
        return MX::op(dat[k][L], dat[k][R - (1 << k)]);
    }

    template <class F>
    int max_right(const F check, int L)
    {
        assert(0 <= L && L <= n && check(MX::unit()));
        if (L == n) return n;
        int ok = L, ng = n + 1;
        while (ok + 1 < ng) {
            int  k  = (ok + ng) / 2;
            bool bl = check(prod(L, k));
            if (bl) ok = k;
            if (!bl) ng = k;
        }
        return ok;
    }

    template <class F>
    int min_left(const F check, int R)
    {
        assert(0 <= R && R <= n && check(MX::unit()));
        if (R == 0) return 0;
        int ok = R, ng = -1;
        while (ng + 1 < ok) {
            int  k  = (ok + ng) / 2;
            bool bl = check(prod(k, R));
            if (bl) ok = k;
            if (!bl) ng = k;
        }
        return ok;
    }
};

// END: ds/sparse_table/sparse_table.hpp
#line 5 "string/suffix_array.hpp"
// BEGIN: ds/segtree/segtree.hpp
#line 1 "ds/segtree/segtree.hpp"

template <class Monoid>
struct SegTree {
    using MX         = Monoid;
    using X          = typename MX::value_type;
    using value_type = X;
    vc<X> dat;
    int   n, log, size;

    SegTree() {}

    SegTree(int n)
    {
        build(n);
    }

    template <typename F>
    SegTree(int n, F f)
    {
        build(n, f);
    }

    SegTree(const vc<X> &v)
    {
        build(v);
    }

    void build(int m)
    {
        build(m, [](int i) -> X {
            return MX::unit();
        });
    }

    void build(const vc<X> &v)
    {
        build(len(v), [&](int i) -> X {
            return v[i];
        });
    }

    template <typename F>
    void build(int m, F f)
    {
        n = m, log = 1;
        while ((1 << log) < n)
            ++log;
        size = 1 << log;
        dat.assign(size << 1, MX::unit());
        FOR(i, n) dat[size + i] = f(i);
        FOR_R(i, 1, size) update(i);
    }

    X get(int i)
    {
        return dat[size + i];
    }

    vc<X> get_all()
    {
        return {dat.begin() + size, dat.begin() + size + n};
    }

    void update(int i)
    {
        dat[i] = Monoid::op(dat[2 * i], dat[2 * i + 1]);
    }

    void set(int i, const X &x)
    {
        assert(i < n);
        dat[i += size] = x;
        while (i >>= 1)
            update(i);
    }

    void multiply(int i, const X &x)
    {
        assert(i < n);
        i += size;
        dat[i] = Monoid::op(dat[i], x);
        while (i >>= 1)
            update(i);
    }

    X prod(int L, int R)
    {
        assert(0 <= L && L <= R && R <= n);
        X vl = Monoid::unit(), vr = Monoid::unit();
        L += size, R += size;
        while (L < R) {
            if (L & 1) vl = Monoid::op(vl, dat[L++]);
            if (R & 1) vr = Monoid::op(dat[--R], vr);
            L >>= 1, R >>= 1;
        }
        return Monoid::op(vl, vr);
    }

    X prod_all()
    {
        return dat[1];
    }

    template <class F>
    int max_right(F check, int L)
    {
        assert(0 <= L && L <= n && check(Monoid::unit()));
        if (L == n) return n;
        L += size;
        X sm = Monoid::unit();
        do {
            while (L % 2 == 0)
                L >>= 1;
            if (!check(Monoid::op(sm, dat[L]))) {
                while (L < size) {
                    L = 2 * L;
                    if (check(Monoid::op(sm, dat[L]))) {
                        sm = Monoid::op(sm, dat[L++]);
                    }
                }
                return L - size;
            }
            sm = Monoid::op(sm, dat[L++]);
        } while ((L & -L) != L);
        return n;
    }

    template <class F>
    int min_left(F check, int R)
    {
        assert(0 <= R && R <= n && check(Monoid::unit()));
        if (R == 0) return 0;
        R += size;
        X sm = Monoid::unit();
        do {
            --R;
            while (R > 1 && (R % 2))
                R >>= 1;
            if (!check(Monoid::op(dat[R], sm))) {
                while (R < size) {
                    R = 2 * R + 1;
                    if (check(Monoid::op(dat[R], sm))) {
                        sm = Monoid::op(dat[R--], sm);
                    }
                }
                return R + 1 - size;
            }
            sm = Monoid::op(dat[R], sm);
        } while ((R & -R) != R);
        return 0;
    }

    // prod_{l<=i<r} A[i xor x]
    X xor_prod(int l, int r, int xor_val)
    {
        static_assert(Monoid::commute);
        X x = Monoid::unit();
        for (int k = 0; k < log + 1; ++k) {
            if (l >= r) break;
            if (l & 1) {
                x = Monoid::op(x, dat[(size >> k) + ((l++) ^ xor_val)]);
            }
            if (r & 1) {
                x = Monoid::op(x, dat[(size >> k) + ((--r) ^ xor_val)]);
            }
            l /= 2, r /= 2, xor_val /= 2;
        }
        return x;
    }
};

// END: ds/segtree/segtree.hpp
#line 6 "string/suffix_array.hpp"

// 辞書順 i 番目の suffix が j 文字目始まりであるとき、
// SA[i] = j, ISA[j] = i
// |S|>0 を前提（そうでない場合 dummy 文字を追加して利用せよ）
template <bool USE_SPARSE_TABLE = true>
struct Suffix_Array {
    vc<int> SA;
    vc<int> ISA;
    vc<int> LCP;
    using Mono    = Monoid_Min<int>;
    using SegType = conditional_t<USE_SPARSE_TABLE, Sparse_Table<Mono>, SegTree<Mono>>;
    SegType seg;
    bool    build_seg;

    Suffix_Array() {}

    Suffix_Array(string &s)
    {
        build_seg = 0;
        assert(len(s) > 0);
        char first = 127, last = 0;
        for (auto &&c : s) {
            chmin(first, c);
            chmax(last, c);
        }
        SA = calc_suffix_array(s, first, last);
        calc_LCP(s);
    }

    Suffix_Array(vc<int> s)
    {
        build_seg = 0;
        assert(len(s) > 0);
        SA = calc_suffix_array(s);
        calc_LCP(s);
    }

    // lcp(S[i:], S[j:])
    int lcp(int i, int j)
    {
        if (!build_seg) {
            build_seg = true;
            seg.build(LCP);
        }
        int n = len(SA);
        if (i == n || j == n) return 0;
        if (i == j) return n - i;
        i = ISA[i], j = ISA[j];
        if (i > j) swap(i, j);
        return seg.prod(i, j);
    }

    // S[i:] との lcp が n 以上であるような半開区間
    pair<int, int> lcp_range(int i, int n)
    {
        if (!build_seg) {
            build_seg = true;
            seg.build(LCP);
        }
        i     = ISA[i];
        int a = seg.min_left(
            [&](auto e) -> bool {
                return e >= n;
            },
            i);
        int b = seg.max_right(
            [&](auto e) -> bool {
                return e >= n;
            },
            i);
        return {a, b + 1};
    }

    // -1: S[L1:R1) < S[L2, R2)
    //  0: S[L1:R1) = S[L2, R2)
    // +1: S[L1:R1) > S[L2, R2)
    int compare(int L1, int R1, int L2, int R2)
    {
        int n1 = R1 - L1, n2 = R2 - L2;
        int n = lcp(L1, L2);
        if (n == n1 && n == n2) return 0;
        if (n == n1) return -1;
        if (n == n2) return 1;
        return (ISA[L1 + n] > ISA[L2 + n] ? 1 : -1);
    }

private:
    void induced_sort(const vc<int> &vect, int val_range, vc<int> &SA, const vc<bool> &sl, const vc<int> &lms_idx)
    {
        vc<int> l(val_range, 0), r(val_range, 0);
        for (int c : vect) {
            if (c + 1 < val_range) ++l[c + 1];
            ++r[c];
        }
        partial_sum(l.begin(), l.end(), l.begin());
        partial_sum(r.begin(), r.end(), r.begin());
        fill(SA.begin(), SA.end(), -1);
        for (int i = (int)lms_idx.size() - 1; i >= 0; --i)
            SA[--r[vect[lms_idx[i]]]] = lms_idx[i];
        for (int i : SA)
            if (i >= 1 && sl[i - 1]) SA[l[vect[i - 1]]++] = i - 1;
        fill(r.begin(), r.end(), 0);
        for (int c : vect)
            ++r[c];
        partial_sum(r.begin(), r.end(), r.begin());
        for (int k = (int)SA.size() - 1, i = SA[k]; k >= 1; --k, i = SA[k])
            if (i >= 1 && !sl[i - 1]) {
                SA[--r[vect[i - 1]]] = i - 1;
            }
    }

    vc<int> SA_IS(const vc<int> &vect, int val_range)
    {
        const int n = vect.size();
        vc<int>   SA(n), lms_idx;
        vc<bool>  sl(n);
        sl[n - 1] = false;
        for (int i = n - 2; i >= 0; --i) {
            sl[i] = (vect[i] > vect[i + 1] || (vect[i] == vect[i + 1] && sl[i + 1]));
            if (sl[i] && !sl[i + 1]) lms_idx.push_back(i + 1);
        }
        reverse(lms_idx.begin(), lms_idx.end());
        induced_sort(vect, val_range, SA, sl, lms_idx);
        vc<int> new_lms_idx(lms_idx.size()), lms_vec(lms_idx.size());
        for (int i = 0, k = 0; i < n; ++i)
            if (!sl[SA[i]] && SA[i] >= 1 && sl[SA[i] - 1]) {
                new_lms_idx[k++] = SA[i];
            }
        int cur   = 0;
        SA[n - 1] = cur;
        for (size_t k = 1; k < new_lms_idx.size(); ++k) {
            int i = new_lms_idx[k - 1], j = new_lms_idx[k];
            if (vect[i] != vect[j]) {
                SA[j] = ++cur;
                continue;
            }
            bool flag = false;
            for (int a = i + 1, b = j + 1;; ++a, ++b) {
                if (vect[a] != vect[b]) {
                    flag = true;
                    break;
                }
                if ((!sl[a] && sl[a - 1]) || (!sl[b] && sl[b - 1])) {
                    flag = !((!sl[a] && sl[a - 1]) && (!sl[b] && sl[b - 1]));
                    break;
                }
            }
            SA[j] = (flag ? ++cur : cur);
        }
        for (size_t i = 0; i < lms_idx.size(); ++i)
            lms_vec[i] = SA[lms_idx[i]];
        if (cur + 1 < (int)lms_idx.size()) {
            auto lms_SA = SA_IS(lms_vec, cur + 1);
            for (size_t i = 0; i < lms_idx.size(); ++i) {
                new_lms_idx[i] = lms_idx[lms_SA[i]];
            }
        }
        induced_sort(vect, val_range, SA, sl, new_lms_idx);
        return SA;
    }

    vc<int> calc_suffix_array(const string &s, const char first = 'a', const char last = 'z')
    {
        vc<int> vect(s.size() + 1);
        copy(begin(s), end(s), begin(vect));
        for (auto &x : vect)
            x -= (int)first - 1;
        vect.back() = 0;
        auto ret    = SA_IS(vect, (int)last - (int)first + 2);
        ret.erase(ret.begin());
        return ret;
    }

    vc<int> calc_suffix_array(const vc<int> &s)
    {
        vc<int> ss = s;
        UNIQUE(ss);

        vc<int> vect(s.size() + 1);
        copy(all(s), vect.begin());
        for (auto &x : vect)
            x = LB(ss, x) + 1;
        vect.back() = 0;
        auto ret    = SA_IS(vect, MAX(vect) + 2);
        ret.erase(ret.begin());
        return ret;
    }

    template <typename STRING>
    void calc_LCP(const STRING &s)
    {
        int n = s.size(), k = 0;
        ISA.resize(n);
        LCP.resize(n);
        for (int i = 0; i < n; i++)
            ISA[SA[i]] = i;
        for (int i = 0; i < n; i++, k ? k-- : 0) {
            if (ISA[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = SA[ISA[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            LCP[ISA[i]] = k;
        }
        LCP.resize(n - 1);
    }
};  // END: string/suffix_array.hpp

#line 6 "main.cpp"

ll cnt_distinct_substr(string S)
{
    ll              N = len(S);
    Suffix_Array<0> sa(S);
    ll              ANS = N * (N + 1) / 2;
    ANS -= SUM<ll>(sa.LCP);
    return ANS;
}

string gen(ll N, ll M)
{
    ll lo = ceil<ll>(8 * M, 10);
    ll hi = floor<ll>(12 * M, 10);
    if (lo <= N && N <= hi) {
        return string(N, '0');
    }
    if (hi < 2 * N - 1) return {};
    FOR(a, N + 1)
    {
        ll b = N - a;
        ll x = 0;
        x += a;
        x += b;
        x += a * b;
        if (lo <= x && x <= hi) {
            string S;
            FOR(a) S += '0';
            FOR(b) S += '1';
            return S;
        }
    }

    string S = substring_abundant_string(N);
    ll     K = cnt_distinct_substr(S);
    if (lo <= K && K <= hi) return S;
    assert(hi < K);

    // n 個変更 -> ok とは hi 以下になること
    ll n = binary_search(
        [&](ll n) -> bool {
            string T       = S;
            FOR(i, n) T[i] = '0';
            ll K           = cnt_distinct_substr(T);
            return K <= hi;
        },
        N, 0, 0);
    FOR(i, n) S[i] = '0';
    return S;
    return {};
}

void test(ll N)
{
    string god = substring_abundant_string(N);
    ll     K   = cnt_distinct_substr(god);
    FOR(M, N, K + 1)
    {
        //       if(N<0.8M && 1.2M<2N-1)continue;
        if (10 * N < 8 * M && 12 * M < 10 * (N + N - 1)) continue;
        if (M % 100 != 0) continue;
        string X = gen(N, M);
        if (X.empty()) {
            SHOW("NG", N, M);
        } else {
            ll x = cnt_distinct_substr(X);
            SHOW(N, M, x);
            assert(8 * M <= 10 * x && 10 * x <= 12 * M);
        }
    }
    print("OK", N);
    flush();
}

void solve()
{
    LL(N, M);
    auto S = gen(N, M);
    if (S.empty()) return print(-1);
    print(S);
}

signed main()
{
    // FOR(N, 1, 100) test(N);
    // test(1000);
    INT(T);
    FOR(T)
    solve();
}  // END: main.cpp

#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
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

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

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
    do c = ibuf[pil++];
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

void rd(int &x) { rd_integer(x); }

void rd(ll &x) { rd_integer(x); }

void rd(i128 &x) { rd_integer(x); }

void rd(u32 &x) { rd_integer(x); }

void rd(u64 &x) { rd_integer(x); }

void rd(u128 &x) { rd_integer(x); }

void rd(double &x) { rd_real(x); }

void rd(long double &x) { rd_real(x); }

void rd(f128 &x) { rd_real(x); }

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
    for (auto &d : x) rd(d);
}

template <class T>
void rd(vc<T> &x)
{
    for (auto &d : x) rd(d);
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
    for (char c : s) wt(c);
}

void wt(const char *s)
{
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++) wt(s[i]);
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

void wt(int x) { wt_integer(x); }

void wt(ll x) { wt_integer(x); }

void wt(i128 x) { wt_integer(x); }

void wt(u32 x) { wt_integer(x); }

void wt(u64 x) { wt_integer(x); }

void wt(u128 x) { wt_integer(x); }

void wt(double x) { wt_real(x); }

void wt(long double x) { wt_real(x); }

void wt(f128 x) { wt_real(x); }

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

void print() { wt('\n'); }

template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail)
{
    wt(head);
    if (sizeof...(Tail)) wt(' ');
    print(forward<Tail>(tail)...);
}

// gcc expansion. called automaticall after main.
void __attribute__((destructor)) _d() { flush(); }
}  // namespace fastio

using fastio::flush;
using fastio::print;
using fastio::read;

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

void YES(bool t = 1) { print(t ? "YES" : "NO"); }

void NO(bool t = 1) { YES(!t); }

void Yes(bool t = 1) { print(t ? "Yes" : "No"); }

void No(bool t = 1) { Yes(!t); }

void yes(bool t = 1) { print(t ? "yes" : "no"); }

void no(bool t = 1) { yes(!t); }

void YA(bool t = 1) { print(t ? "YA" : "TIDAK"); }

void TIDAK(bool t = 1) { YA(!t); }

void solve()
{
    int n;
    read(n);
    vector<int> g(n), r(n);
    int         haszero = 0;
    vector<int> bullk(2e5 + 50);
    for (int i = 0; i < n; i++) {
        read(g[i]);
        read(r[i]);
        if (g[i] == 0) haszero = 1;
        bullk[g[i]]++;
    }
    int gsum = accumulate(all(g), 0);
    for (int i = 0; i <= gsum / 2; i++) {
        while (bullk[i] >= 3) {
            bullk[i] -= 2;
            bullk[i * 2]++;
        }
    }
    vector<int> candi;
    for (int i = 1; i <= gsum / 2; i++) {
        assert(bullk[i] <= 2);
        for (int j = 0; j < bullk[i]; j++) {
            candi.pb(i);
        }
    }
    bitset<int(1e5 + 50)> dp;
    dp[0] = 1;
    int m = candi.size();
    assert(m <= ceil(sqrt(2e5)) * ceil(log(2e5)));
    for (int i = 0; i < m; i++) {
        int cur = candi[i];
        dp |= dp << cur;
    }
    vector<int> achieve(2e5 + 50);
    for (int i = 0; i <= (gsum) / 2; i++) {
        if (dp[i]) {
            achieve[gsum - 2 * i] = 1;
        }
    }
    int gc = accumulate(all(r), 0, gcd<int, int>);
    for (i64 i = 0; i * gc <= 2e5; i++) {
        if (!haszero && i * gc == gsum) continue;
        if (achieve[gc * i]) {
            print("Y");
            return;
        }
    }
    print("N");
}

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
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
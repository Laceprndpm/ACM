#include <cassert>
#include <iostream>
#include <utility>
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
void smart_print(std::ostream &os, const T &val, int indent = 0)
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
void dbg_wt(const T &val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail)
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
constexpr int P = 998244353;
constexpr int N = 4 * 4 * 1000 * 1000;

int qpow(int x, int y)
{
    int res(1);
    while (y) {
        if (y & 1) res = 1ll * res * x % P;
        x = 1ll * x * x % P;
        y >>= 1;
    }
    return res;
}

int r[N];

void ntt(int *x, int lim, int opt)
{
    int i, j, k, m, gn, g, tmp;
    for (i = 0; i < lim; ++i)
        if (r[i] < i) swap(x[i], x[r[i]]);
    for (m = 2; m <= lim; m <<= 1) {
        k  = m >> 1;
        gn = qpow(3, (P - 1) / m);
        for (i = 0; i < lim; i += m) {
            g = 1;
            for (j = 0; j < k; ++j, g = 1ll * g * gn % P) {
                tmp          = 1ll * x[i + j + k] * g % P;
                x[i + j + k] = (x[i + j] - tmp + P) % P;
                x[i + j]     = (x[i + j] + tmp) % P;
            }
        }
    }
    if (opt == -1) {
        reverse(x + 1, x + lim);
        int inv = qpow(lim, P - 2);
        for (i = 0; i < lim; ++i) x[i] = 1ll * x[i] * inv % P;
    }
}

// floor(p / i) * i + p % i == p
// floor(p / i) * i + p % i == 0 (mod p)
// inv[i] == -inv[p % i] * floor(p / i)

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    auto   zip   = [m](int x, int y) constexpr { return y * (2 * m) + x; };  // [0, 2 * n * m - 1]
    auto   unzip = [m](i64 c) constexpr -> pair<int, int> { return pair<int, int>(c % (2 * m), c / (2 * m)); };
    int    x = 0, y = 0;
    int    mx_x = 0, mx_y = 0, mn_x = 0, mn_y = 0;
    string s;
    cin >> s;
    for (char c : s) {
        switch (c) {
            case 'U': y--; break;
            case 'D': y++; break;
            case 'L': x--; break;
            case 'R': x++; break;
        }
        mx_x = max(mx_x, x);
        mn_x = min(mn_x, x);
        mx_y = max(mx_y, y);
        mn_y = min(mn_y, y);
    }
    if (mx_x - mn_x >= m || mx_y - mn_y >= n) {
        if (k == 0) {
            cout << n * m << '\n';
        } else {
            cout << 0 << '\n';
        }
        return;
    }
    int len     = 2 * (4 * n * m + 1) - 1;
    int reallen = 1;
    while (reallen < len) {
        reallen <<= 1;
    }
    vector<int> animo(reallen);
    vector<int> px(reallen);
    for (int i = 0; i < reallen; ++i) r[i] = (i & 1) * (reallen >> 1) + (r[i >> 1] >> 1);
    for (int iy = -mn_y; iy < n - mx_y; iy++) {
        fill(animo.begin() + zip(-mn_x + m, iy + n), animo.begin() + zip(2 * m - mx_x, iy + n), 1);
    }
    int death = (n - mx_y + mn_y) * (m - mx_x + mn_x) - k;
    x = m, y = n;
    px[4 * n * m - zip(x, y)] = 1;
    for (char c : s) {
        switch (c) {
            case 'U': y++; break;
            case 'D': y--; break;
            case 'L': x++; break;
            case 'R': x--; break;
        }
        px[4 * n * m - zip(x, y)] = 1;
    }
    ntt(px.data(), reallen, 1);
    ntt(animo.data(), reallen, 1);
    for (int i = 0; i < reallen; i++) {
        px[i] = i64(px[i]) * animo[i] % P;
    }
    ntt(px.data(), reallen, -1);
    int ans = 0;
    for (int c = 4 * n * m; c < 6 * n * m; c++) {
        int j         = c - 4 * n * m;
        auto [ax, ay] = unzip(j);
        if (ax < 0 || ay < 0 || ax >= m || ay >= n) continue;
        if (px[c] != death) continue;
        ans++;
    }
    cout << ans << '\n';
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

// tmp =
// [
//   [1, 2, 2, 1, 0],
//   [2, 4, 4, 2, 0],
//   [2, 4, 5, 3, 1],
//   [1, 2, 3, 2, 1]
// ]
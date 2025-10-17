#include <cassert>
#include <deque>
#include <iostream>
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

void solve()
{
    int A, B;
    cin >> A >> B;
    int X, Y;
    cin >> X >> Y;
    int vA   = A;
    int vB   = B;
    int cntA = 0;
    int cntB = 0;
    while (vA && !(vA & 1)) {
        vA >>= 1;
        cntA++;
    }
    while (vB && !(vB & 1)) {
        vB >>= 1;
        cntB++;
    }
    if ((vA && X % vA != 0) || (vB && Y % vB != 0)) {
        cout << -1 << '\n';
        return;
    }
    int        bX = vA ? X / vA : 0;
    int        bY = vB ? Y / vB : 0;
    int        vX = bX, vY = bY;
    int        cntX = 0, cntY = 0;
    deque<int> opX;
    bool       XA = 0;
    bool       XB = 0;
    if (X != A)
        for (int i = cntA - 1; i >= 0; i--) {
            if (bX >> i & 1) {
                opX.pb(1);
            } else {
                opX.pb(0);
            }
        }
    else {
        XA = 1;
    }
    deque<int> opY;
    if (Y != B)
        for (int i = cntB - 1; i >= 0; i--) {
            if (bY >> i & 1) {
                opY.pb(1);
            } else {
                opY.pb(0);
            }
        }
    else {
        XB = 1;
    }
    reverse(all(opX)), reverse(all(opY));
    while (!opX.empty() && opX.front() == 0) {
        opX.pop_front();
    }
    while (!opY.empty() && opY.front() == 0) {
        opY.pop_front();
    }
    while (opX.size() < opY.size()) {
        opX.push_front(0);
    }
    while (opY.size() < opX.size()) {
        opY.push_front(0);
    }
    assert(opX.size() == opY.size());
    int n = opX.size();
    cout << n << '\n';
    int lastX = 0, lastY = 0;
    if (XA) {
        lastX = A;
    }
    if (XB) {
        lastY = B;
    }
    for (int i = 0; i < n; i++) {
        cout << lastX << ' ' << lastY << ' ';
        if (opX[i] == 1 || XA) {
            cout << A << ' ';
            lastX = (lastX + A) / 2;
        } else {
            cout << 0 << ' ';
            lastX = lastX / 2;
        }
        if (opY[i] == 1 || XB) {
            cout << B << ' ';
            lastY = (lastY + B) / 2;
        } else {
            cout << 0 << ' ';
            lastY = lastY / 2;
        }
        cout << '\n';
    }
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
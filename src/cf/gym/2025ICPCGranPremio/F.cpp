#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
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
// #pragma GCC optimize("-falign-jumps")
// #pragma GCC optimize("-falign-loops")
// #pragma GCC optimize("-falign-labels")
// #pragma GCC optimize("-fdevirtualize")
// #pragma GCC optimize("-fcaller-saves")
// #pragma GCC optimize("-fcrossjumping")
// #pragma GCC optimize("-fthread-jumps")
// #pragma GCC optimize("-funroll-loops")
// #pragma GCC optimize("-fwhole-program")
// #pragma GCC optimize("-freorder-blocks")
// #pragma GCC optimize("-fschedule-insns")
// #pragma GCC optimize("inline-functions")
// #pragma GCC optimize("-ftree-tail-merge")
// #pragma GCC optimize("-fschedule-insns2")
// #pragma GCC optimize("-fstrict-aliasing")
// #pragma GCC optimize("-fstrict-overflow")
// #pragma GCC optimize("-falign-functions")
// #pragma GCC optimize("-fcse-skip-blocks")
// #pragma GCC optimize("-fcse-follow-jumps")
// #pragma GCC optimize("-fsched-interblock")
// #pragma GCC optimize("-fpartial-inlining")
// #pragma GCC optimize("no-stack-protector")
// #pragma GCC optimize("-freorder-functions")
// #pragma GCC optimize("-findirect-inlining")
// #pragma GCC optimize("-fhoist-adjacent-loads")
// #pragma GCC optimize("-frerun-cse-after-loop")
// #pragma GCC optimize("inline-small-functions")
// #pragma GCC optimize("-finline-small-functions")
// #pragma GCC optimize("-ftree-switch-conversion")
// #pragma GCC optimize("-foptimize-sibling-calls")
// #pragma GCC optimize("-fexpensive-optimizations")
// #pragma GCC optimize("-funsafe-loop-optimizations")
// #pragma GCC optimize("inline-functions-called-once")
// #pragma GCC optimize("-fdelete-null-pointer-checks")
// #pragma GCC optimize(2)
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
constexpr int N = 1e2;
constexpr int M = 1e2;
short         dp[N + 1][M + 1][N + 1][M + 1];
char          board[N + 2][M + 2];
bool          vis[N + 1][M + 1];
bool          vis1[N + 1][M + 1];

int dist[N + 1][M + 1];

void init()
{
    memset(dp, 0x3f, sizeof dp);
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);
    memset(vis1, 0, sizeof vis);
}

void solve()
{
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", board[i] + 1);
    }
    for (int i = 1; i <= n; i++) {
        board[i][0]     = '1';
        board[i][m + 1] = '1';
    }
    for (int j = 1; j <= m; j++) {
        board[0][j]     = '1';
        board[n + 1][j] = '1';
    }
    int ax, ay;
    scanf("%d%d", &ax, &ay);
    ax++, ay++;
    int dx, dy;
    scanf("%d%d", &dx, &dy);
    dx++, dy++;
    int k;
    scanf("%d", &k);
    vector<string> allord(k);
    for (int i = 0; i < k; i++) {
        cin >> allord[i];
    }
    deque<pair<int, int>> candi;
    candi.pb({ax, ay});
    vis1[ax][ay] = 1;
    while (!candi.empty()) {
        auto [i, j] = candi.front();
        candi.pop_front();
        for (string& ords : allord) {
            int   x = i, y = j;
            short movement = 0;
            for (char c : ords) {
                switch (c) {
                    case 'U':
                        if (board[x - 1][y] == '1') continue;
                        --x;
                        break;
                    case 'D':
                        if (board[x + 1][y] == '1') continue;
                        ++x;
                        break;
                    case 'L':
                        if (board[x][y - 1] == '1') continue;
                        --y;
                        break;
                    case 'R':
                        if (board[x][y + 1] == '1') continue;
                        ++y;
                        break;
                }
                ++movement;
            }
            if (!vis1[x][y]) {
                candi.pb({x, y});
                vis1[x][y] = 1;
            }
            dp[i][j][x][y] = min(dp[i][j][x][y], movement);
        }
    }

    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
    pq.push({0, ax, ay});
    dist[ax][ay] = 0;
    while (!pq.empty()) {
        auto [curd, curx, cury] = pq.top();
        pq.pop();
        if (vis[curx][cury]) continue;
        vis[curx][cury] = 1;
        if (curx == dx && cury == dy) break;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (dp[curx][cury][i][j] == 0x3f3f) continue;
                if (curd + (int)dp[curx][cury][i][j] < dist[i][j]) {
                    dist[i][j] = curd + (int)dp[curx][cury][i][j];
                    pq.push({dist[i][j], i, j});
                }
            }
        }
    }
    if (!vis[dx][dy]) {
        dist[dx][dy] = -1;
    }
    printf("%d", dist[dx][dy]);
}

signed main(signed argc, char** argv)
{
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
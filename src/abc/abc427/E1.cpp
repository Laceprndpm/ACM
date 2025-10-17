#include <cstring>
#include <deque>
#include <iostream>
#include <tuple>
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

constexpr int MAXN1 = 15;
constexpr int MAXN2 = 42;
int           dp[MAXN1][MAXN1][MAXN1][MAXN1][MAXN2][MAXN2];
char          graph[MAXN1][MAXN1][MAXN1][MAXN1][MAXN2][MAXN2];
int           ok[MAXN1][MAXN1][MAXN1][MAXN1];

void solve()
{
    int h, w;
    cin >> h >> w;
    vector<string> board(h + 2);
    for (int i = 1; i <= h; i++) {
        cin >> board[i];
        board[i] = '.' + board[i] + '.';
    }
    board[0] = board[h + 1] = string(w + 2, '.');
    int tx = -1, ty = -1;
    int mnXsharp = h + 1;
    int mxXsharp = 0;
    int mnYsharp = w + 1;
    int mxYsharp = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (board[i][j] == 'T') {
                tx = i, ty = j;
            }
            if (board[i][j] == '#') {
                mnXsharp = min(mnXsharp, i);
                mxXsharp = max(mxXsharp, i);
                mnYsharp = min(mnYsharp, j);
                mxYsharp = max(mxYsharp, j);
            }
        }
    }
    auto cro = [&](int a, int b, int c, int d) -> bool {
        if (b < mnXsharp || a > mxXsharp || d < mnYsharp || c > mxYsharp || a > b || c > d) {
            return false;
        } else {
            return true;
        }
    };
    for (int mnX = 0; mnX <= h + 1; mnX++) {
        for (int mxX = mnX; mxX <= h + 1; mxX++) {
            for (int mnY = 0; mnY <= w + 1; mnY++) {
                for (int mxY = mnY; mxY <= w + 1; mxY++) {
                    int cur = 1;
                    for (int x = 0; x <= h + 1; x++) {
                        for (int y = 0; y <= w + 1; y++) {
                            if (mnX <= x && x <= mxX && mnY <= y && y <= mxY && board[x][y] == '#') {
                                graph[mnX][mxX][mnY][mxY][x][y] = '#';
                                cur                             = 0;
                            } else {
                                graph[mnX][mxX][mnY][mxY][x][y] = '.';
                            }
                        }
                    }
                    ok[mnX][mxX][mnY][mxY] = cur;
                }
            }
        }
    }
    int  dx[] = {0, 0, -1, 1};
    int  dy[] = {-1, 1, 0, 0};
    auto bfs  = [&]() -> int {
        deque<tuple<int, int, int, int, int, int, int>> que;
        que.pb({0, tx, ty, mnXsharp, mxXsharp, mnYsharp, mxYsharp});
        dp[mnXsharp][mxXsharp][mnYsharp][mxYsharp][tx + 12][ty + 12] = 1;
        while (!que.empty()) {
            auto [dis, x, y, mnX, mxX, mnY, mxY] = que.front();
            que.pop_front();
            if (mnX > mxX || mnY > mxY || ok[mnX][mxX][mnY][mxY]) {
                return dis;
            }
            for (int j = 0; j < 4; j++) {
                int nx = dx[j] + x, ny = dy[j] + y;
                int nmnX = max(mnX, 1 + (nx - tx));
                int nmxX = min(mxX, h - (tx - nx));
                int nmnY = max(mnY, 1 + (ny - ty));
                int nmxY = min(mxY, w - (ty - ny));
                if ((nx < 1 || nx > h || ny < 1 || ny > w || graph[mnX][mxX][mnY][mxY][nx][ny] == '.')
                    && !dp[nmnX][nmxX][nmnY][nmxY][nx + 12][ny + 12]) {
                    dp[nmnX][nmxX][nmnY][nmxY][nx + 12][ny + 12] = 1;
                    que.pb({dis + 1, nx, ny, nmnX, nmxX, nmnY, nmxY});
                }
            }
        }
        return -1;
    };
    cout << bfs() << '\n';
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
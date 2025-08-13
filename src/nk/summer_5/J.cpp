#include <bits/stdc++.h>

#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <utility>
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
#define len(x)  int(x.size())
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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> board(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
        }
    }
    deque<array<int, 3>> deq;
    vector<vector<int>>  vis(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= n; i++) {
        vis[i][0]     = 1;
        vis[i][m + 1] = 1;
    }
    for (int j = 1; j <= m; j++) {
        vis[0][j]     = 1;
        vis[n + 1][j] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (board[i][j] == 1) {
                deq.push_back({0, i, j});
                vis[i][j] = 1;
            }
        }
    }
    vector<array<int, 3>> vec;
    vec.reserve(n * m);
    int dx[]  = {1, -1, 0, 0};
    int dy[]  = {0, 0, 1, -1};
    int max_t = 0;
    if (deq.empty()) {
        cout << (n - (n + 1) / 2 + m - (m + 1) / 2) << '\n';
        return;
    }
    while (!deq.empty()) {
        auto [t, x, y] = deq.front();
        max_t          = max(max_t, t);
        deq.pop_front();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (vis[nx][ny]) continue;
            vis[nx][ny] = 1;
            vec.push_back({t + 1, nx, ny});
            deq.push_back({t + 1, nx, ny});
        }
    }
    if (vec.size() <= 1) {
        cout << "0\n";
        return;
    }
    vector<array<int, 2>> prefix_x(max_t + 2, {-INF, INF});
    vector<array<int, 2>> prefix_y(max_t + 2, {-INF, INF});
    for (auto it : vec) {
        int t     = it[0];
        int man_x = it[1], man_y = it[2];
        int nx = man_x + man_y, ny = man_x - man_y;

        prefix_x[t][0] = max(prefix_x[t][0], nx);
        prefix_x[t][1] = min(prefix_x[t][1], nx);

        prefix_y[t][0] = max(prefix_y[t][0], ny);
        prefix_y[t][1] = min(prefix_y[t][1], ny);
    }
    for (int t = max_t - 1; t >= 1; t--) {
        prefix_x[t][0] = max(prefix_x[t][0], prefix_x[t + 1][0]);
        prefix_x[t][1] = min(prefix_x[t][1], prefix_x[t + 1][1]);
        prefix_y[t][0] = max(prefix_y[t][0], prefix_y[t + 1][0]);
        prefix_y[t][1] = min(prefix_y[t][1], prefix_y[t + 1][1]);
    }
    prefix_x[0][0] = prefix_x[0][1] = 0;
    prefix_y[0][0] = prefix_y[0][1] = 0;
    int ans                         = max_t;
    for (int i = 1; i <= max_t; i++) {
        auto [hi_x, lo_x] = prefix_x[i];
        auto [hi_y, lo_y] = prefix_y[i];
        int t             = i - 1;
        if (max(hi_x - lo_x, hi_y - lo_y) <= 2 * t) {
            ans = t;
            break;
        }
        // 所有点到未知点x的曼哈顿距离<=t <=>所有点间最大切比雪夫距离<=2t+1?
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
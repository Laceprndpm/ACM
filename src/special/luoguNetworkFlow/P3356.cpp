#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
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
struct MCFGraph {
    struct _Edge {
        int u, v, c, f;

        _Edge(int u, int v, int c, int f) : u(u), v(v), c(c), f(f) {}
    };

    const int                     n;
    std::vector<_Edge>            e;
    std::vector<std::vector<int>> g;
    std::vector<i64>              h, dis;
    std::vector<int>              pre;

    bool spfa(int s, int t)
    {
        dis.assign(n, std::numeric_limits<i64>::max());
        pre.assign(n, -1);
        std::deque<int>   que;
        std::vector<bool> inq(n, false);
        dis[s] = 0;
        inq[s] = true;
        que.emplace_back(s);
        while (!que.empty()) {
            int u  = que.front();
            i64 d  = dis[u];
            inq[u] = false;
            que.pop_front();
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + f) {
                    dis[v] = d + f;
                    pre[v] = i;
                    if (!inq[v]) {
                        que.emplace_back(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return dis[t] != std::numeric_limits<i64>::max();
    }

    bool dijkstra(int s, int t)
    {
        dis.assign(n, std::numeric_limits<i64>::max());
        pre.assign(n, -1);
        std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<std::pair<i64, int>>>
            que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            i64 d = que.top().first;
            int u = que.top().second;
            que.pop();
            if (dis[u] < d) continue;
            for (int i : g[u]) {
                int v = e[i].v;
                int c = e[i].c;
                int f = e[i].f;
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<i64>::max();
    }

    MCFGraph(int n) : n(n), g(n) {}

    void addEdge(int u, int v, int c, int f)
    {
        g[u].push_back(e.size());
        e.emplace_back(u, v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(v, u, 0, -f);
    }

    // // 代码同(07A - 费用流（MCFGraph 最小费用可行流）)，但是需要注释掉建边限制。以下为参考：
    // void addEdge(int u, int v, int c, int f)
    // {  // 可行流
    //     if (f < 0) {
    //         g[u].push_back(e.size());
    //         e.emplace_back(u, v, 0, f);
    //         g[v].push_back(e.size());
    //         e.emplace_back(v, u, c, -f);
    //     } else {
    //         g[u].push_back(e.size());
    //         e.emplace_back(u, v, c, f);
    //         g[v].push_back(e.size());
    //         e.emplace_back(v, u, 0, -f);
    //     }
    // }

    std::pair<int, i64> flow(int s, int t)
    {
        int flow = 0;
        i64 cost = 0;
        h.assign(n, 0);

        // init with spfa
        do {
            bool result = spfa(s, t);
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += i64(aug) * h[t];
            if (!result) return std::make_pair(flow, cost);
        } while (0);
        // end

        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = std::numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) aug = std::min(aug, e[pre[i]].c);
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += i64(aug) * h[t];
        }
        return std::make_pair(flow, cost);
    }

    struct Edge {
        int from, to, cap, flow;
    };

    std::vector<Edge> edges()
    {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].v;
            x.to   = e[i].v;
            x.cap  = e[i].c + e[i + 1].c;
            x.flow = e[i + 1].c;
            a.push_back(x);
        }
        return a;
    }
};

void solve()
{
    int n, p, q;
    cin >> n >> p >> q;
    MCFGraph            mcf(p * q * 2 + 1);
    auto                zip   = [&](int y, int x) -> int { return y * (p) + x; };
    auto                unzip = [&](int code) -> pair<int, int> { return {code / p, code % p}; };
    vector<vector<int>> board(q, vector<int>(p));
    for (int y = 0; y < q; y++) {
        for (int x = 0; x < p; x++) {
            cin >> board[y][x];
            switch (board[y][x]) {
                case 2: mcf.addEdge(zip(y, x) * 2, zip(y, x) * 2 + 1, 1, -1); [[fallthrough]];
                case 0: mcf.addEdge(zip(y, x) * 2, zip(y, x) * 2 + 1, INF, 0); break;
                case 1: break;  // do nothing
            }
        }
    }
    for (int y = 0; y < q; y++) {
        for (int x = 0; x < p - 1; x++) {
            mcf.addEdge(zip(y, x) * 2 + 1, zip(y, x + 1) * 2, INF, 0);
        }
    }
    for (int y = 0; y < q - 1; y++) {
        for (int x = 0; x < p; x++) {
            mcf.addEdge(zip(y, x) * 2 + 1, zip(y + 1, x) * 2, INF, 0);
        }
    }
    int s = p * q * 2;
    int t = zip(q - 1, p - 1) * 2 + 1;
    mcf.addEdge(s, zip(0, 0) * 2, n, 0);
    auto [maxflow, mincost] = mcf.flow(s, t);
    auto                res = mcf.edges();
    vector<vector<int>> capti(q, vector<int>(p));
    for (auto e : res) {
        if (e.from % 2 != 0 || e.from == s) continue;

        auto [y, x] = unzip(e.from / 2);
        if (y >= q || x >= p) continue;
        capti[y][x] += e.flow;
    }
    dbg(capti);
    int  cur = 1;
    auto dfs = [&](auto&& dfs, int y, int x) -> void {
        capti[y][x]--;
        assert(board[y][x] == 0 || board[y][x] == 2);
        if (y + 1 < q && capti[y + 1][x]) {
            cout << cur << " 0\n";
            dfs(dfs, y + 1, x);
            return;
        } else if (x + 1 < p && capti[y][x + 1]) {
            cout << cur << " 1\n";
            dfs(dfs, y, x + 1);
            return;
        } else {
            assert(y == q - 1 && x == p - 1);
        }
    };

    for (cur = 1; cur <= n; cur++) {
        dfs(dfs, 0, 0);
    }
    dbg(capti);
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
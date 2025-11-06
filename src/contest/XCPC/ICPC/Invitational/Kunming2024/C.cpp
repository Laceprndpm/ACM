#include <cassert>
#include <iostream>
#include <map>
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
constexpr int inf = 1E9;

template <class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T   cap;

        _Edge(int to, T cap) : to(to), cap(cap) {}
    };

    int                           n;
    std::vector<_Edge>            e;
    std::vector<std::vector<int>> g;
    std::vector<int>              cur, h;

    MaxFlow() {}

    MaxFlow(int n) { init(n); }

    void init(int n)
    {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }

    bool bfs(int s, int t)
    {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }

    T dfs(int u, int t, T f)
    {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int& i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }

    void addEdge(int u, int v, T c)
    {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }

    T flow(int s, int t)
    {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }

    std::vector<bool> minCut()
    {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }

    struct Edge {
        int from;
        int to;
        T   cap;
        T   flow;
    };

    std::vector<Edge> edges()
    {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to   = e[i].to;
            x.cap  = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    map<int, map<int, int>> row;
    map<int, map<int, int>> col;

    for (int i = 1; i <= n; i++) {
        int r, c;
        cin >> r >> c;
        row[r].ins({c, i});
        col[c].ins({r, i + n});
    }
    MaxFlow<int>           mcf(2 * n + 2);
    vector<int>            candidate;
    vector<pair<int, int>> rowid_colid(m);
    vector<pair<int, int>> row_col(m);
    for (int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        int rowid = 0;
        {
            auto rowline = row[r].upper_bound(c);
            if (rowline != row[r].begin() && rowline != row[r].end()) {
                rowline--;
                rowid = rowline->se;
            }
        }
        int colid = 0;
        {
            auto colline = col[c].upper_bound(r);
            if (colline != col[c].begin() && colline != col[c].end()) {
                colline--;
                colid = colline->se;
            }
        }
        if (rowid && colid) {
            mcf.addEdge(rowid, colid, 1);
            candidate.pb(i);
        }
        row_col[i]     = {r, c};
        rowid_colid[i] = {rowid, colid};
    }
    int s = 0, t = 2 * n + 1;
    for (int i = 1; i <= n; i++) {
        mcf.addEdge(0, i, 1);
    }
    for (int i = n + 1; i <= 2 * n; i++) {
        mcf.addEdge(i, t, 1);
    }
    int                    res = mcf.flow(s, t);
    vector<pair<int, int>> ord;
    auto                   choice = mcf.edges();
    vector<int>            vis(m);
    vector<int>            viscastle(2 * n + 1);
    for (int j = 0; auto edge : choice) {
        if (edge.from == s || edge.to == t) continue;
        if (edge.flow) {
            vis[candidate[j]] = 1;
            auto [r, c]       = rowid_colid[candidate[j]];
            viscastle[r] = viscastle[c] = 1;
            ord.pb({2, candidate[j]});
        }
        j++;
    }
    viscastle[0] = 1;
    for (int j = 0; j < m; j++) {
        if (vis[j]) continue;
        auto [rid, cid] = rowid_colid[j];
        int val         = (int(!viscastle[rid]) + int(!viscastle[cid]));
        assert(val == 0 || val == 1);
        viscastle[rid] = viscastle[cid] = 1;
        ord.pb({val, j});
    }
    sor(ord);
    int         ans = 0;
    vector<int> ansv;
    for (int i = 0; i < k; i++) {
        ansv.pb({ord[i].se + 1});
    }
    for (int i = k; i < m; i++) {
        auto [r, c] = row_col[ord[i].se];
        row[r].insert({c, 0});
        col[c].insert({r, 0});
    }
    for (const auto& [_, line] : row) {
        for (auto it = line.begin(); it != line.end() && next(it) != line.end(); it++) {
            if (next(it)->second && it->second) {
                ans++;
            }
        }
    }
    for (const auto& [_, line] : col) {
        for (auto it = line.begin(); it != line.end() && next(it) != line.end(); it++) {
            if (next(it)->second && it->second) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
    for (int v : ansv) {
        cout << v << ' ';
    }
    cout << '\n';
}

// 1
// 8 6 4
// 1 3
// 2 1
// 2 6
// 4 1
// 4 7
// 6 1
// 6 3
// 6 6

// 2 3
// 3 1
// 4 3
// 4 6
// 5 2
// 6 4

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
#include <algorithm>
#include <cassert>
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

template <>
void smart_print(std::ostream& os, const std::pair<int, int>& p, int indent)
{
    os << "(";
    smart_print(os, p.first, indent);  // 递归处理 first
    os << ", ";
    smart_print(os, p.second, indent);  // 递归处理 second
    os << ")";
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
struct HLD {
    int                            n;
    std::vector<int>               siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>>  adj;
    int                            cur;
    vector<vector<pair<int, int>>> top_vec;
    vector<int>                    ai;

    HLD() {}

    HLD(int n)
    {
        init(n);
    }

    void init(int n)
    {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});

        //
        top_vec.resize(n);  // 按照depth递增
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void work(int root = 0)
    {
        top[root]    = root;
        dep[root]    = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
        dfs3(root);
    }

    void dfs1(int u)
    {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for (auto& v : adj[u]) {
            parent[v] = u;
            dep[v]    = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }

    void dfs2(int u)
    {
        in[u]      = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }

    void dfs3(int u)
    {
        if (ai[u] != 1) {
            top_vec[top[u]].pb({dep[u], ai[u]});
        }
        for (auto v : adj[u]) {
            dfs3(v);
        }
    }

    int lca(int u, int v)
    {
        int init_dep_u = dep[u];
        int init_dep_v = dep[v];

        vector<pair<int, int>> left_arr;
        vector<pair<int, int>> right_arr;
        int                    cur_none1 = 0;
        while (top[u] != top[v] && cur_none1 <= 25) {
            if (dep[top[u]] > dep[top[v]]) {
                const auto& cur_top_vec = top_vec[top[u]];
                int         off_set     = upper_bound(all(cur_top_vec), dep[u],
                                                      [](int a, pair<int, int> b) {
                                              return a < b.fi;  // 找到第一个a > b.fi，前面的留着，后面的滚了
                                          })
                              - bg(cur_top_vec);
                cur_none1 += off_set;
                left_arr.insert(left_arr.end(), bg(top_vec[top[u]]), bg(top_vec[top[u]]) + off_set);
                u = parent[top[u]];
            } else {
                const auto& cur_top_vec = top_vec[top[v]];
                int         off_set     = upper_bound(all(cur_top_vec), dep[v],
                                                      [](int a, pair<int, int> b) {
                                              return a < b.fi;  // 找到第一个a > b.fi，前面的留着，后面的滚了
                                          })
                              - bg(cur_top_vec);
                cur_none1 += off_set;
                right_arr.insert(right_arr.end(), bg(top_vec[top[v]]), bg(top_vec[top[v]]) + off_set);
                v = parent[top[v]];
            }
        }
        if (cur_none1 > 25) {
            return 0;
        }
        assert(top[u] == top[v]);
        if (dep[u] < dep[v]) {
            const auto& cur_top_vec = top_vec[top[v]];
            int         off_set_u   = lower_bound(all(cur_top_vec), dep[u],
                                                  [](pair<int, int> a, int b) {
                                            return a.fi < b;  // 找到第一个a >= b.fi
                                        })
                            - bg(cur_top_vec);
            int off_set_v = upper_bound(all(cur_top_vec), dep[v],
                                        [](int a, pair<int, int> b) {
                                            return a < b.fi;  // 找到第一个a > b.fi
                                        })
                            - bg(cur_top_vec);
            cur_none1 += off_set_v - off_set_u;
            right_arr.insert(right_arr.end(), bg(cur_top_vec) + off_set_u, bg(cur_top_vec) + off_set_v);
        } else {
            // dep[u] > dep[v]
            const auto& cur_top_vec = top_vec[top[v]];
            int         off_set_u   = lower_bound(all(cur_top_vec), dep[u],
                                                  [](pair<int, int> a, int b) {
                                            return a.fi < b;  // 找到第一个a >= b.fi
                                        })
                            - bg(cur_top_vec);
            int off_set_v = upper_bound(all(cur_top_vec), dep[v],
                                        [](int a, pair<int, int> b) {
                                            return a < b.fi;  // 找到第一个a > b.fi
                                        })
                            - bg(cur_top_vec);
            cur_none1 += off_set_u - off_set_v;
            left_arr.insert(left_arr.end(), bg(cur_top_vec) + off_set_v, bg(cur_top_vec) + off_set_u);
        }
        reverse(all(left_arr));
        // now the left_arr and right_arr is depth decress
        //
        //
        int                    lca_depth = min(dep[u], dep[v]);
        vector<pair<int, int>> todo_que;  // val_cnt
        int                    cur_dep = init_dep_u + 1;
        for (auto i : left_arr) {
            todo_que.push_back({1, cur_dep - i.fi - 1});
            todo_que.push_back({i.se, 1});
            cur_dep = i.fi;
        }
        cur_dep = lca_depth - (cur_dep - lca_depth);
        for (auto i : right_arr) {
            todo_que.push_back({1, i.fi - cur_dep - 1});
            todo_que.push_back({i.se, 1});
            cur_dep = i.fi;
        }
        if (cur_dep != init_dep_v) {
            todo_que.push_back({1, init_dep_v - cur_dep + 1});
        }
        dbg(todo_que);
        return 0;
    }

    int dist(int u, int v)
    {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    int jump(int u, int k)
    {
        if (dep[u] < k) {
            return -1;
        }

        int d = dep[u] - k;

        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }

        return seq[in[u] - dep[u] + d];
    }

    bool isAncester(int u, int v)
    {
        return in[u] <= in[v] && in[v] < out[u];
    }

    int rootedParent(int u, int v)
    {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v,
                                   [&](int x, int y) {
                                       return in[x] < in[y];
                                   })
                  - 1;
        return *it;
    }

    int rootedSize(int u, int v)
    {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }

    int rootedLca(int a, int b, int c)
    {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    HLD hld(n + 1);

    hld.ai = ai;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.addEdge(u, v);
    }
    hld.work(1);
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int l, r;
            cin >> l >> r;
            hld.lca(l, r);
        } else {
            int x, d;
            cin >> x >> d;
        }
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
#include <cassert>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_map>
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
/**
 * @brief 并查集
 * 0-index
 */

struct DSU {
    int              n;
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n_) : component(n_), n(n_) { init(n_); }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    int size(int x) { return siz[find(x)]; }

    vector<vector<int>> group(void)
    {
        vector<vector<int>> vec(n);
        for (int i = 0; i < n; i++) {
            vec[f[i]].pb(i);
        }
        vector<vector<int>> res;
        for (auto& i : vec) {
            if (i.empty()) continue;
            res.pb(std::move(i));
        }
        return res;
    }
};

void solve()
{
    // ai - i = aj - j
    // ai + i = ak + k
    // ak + k = ai + i = ai - i = aj + j
    // 不存在
    // 所以两个集合一定只有一个交点i
    //
    int n;
    cin >> n;
    unordered_map<int, int> mpL, mpR;
    vector<int>             arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        mpL[arr[i] - i] = mpR[arr[i] + i] = 0;
    }
    int L = 0, R = 0;
    for (auto it = mpL.begin(); it != mpL.end(); it++) it->second = ++L;
    for (auto it = mpR.begin(); it != mpR.end(); it++) it->second = ++R;
    int                            m = L + R;
    vector<vector<pair<int, int>>> adj(m + 1);
    for (int i = 1; i <= n; i++) {
        int x = mpL[arr[i] - i], y = L + mpR[arr[i] + i];
        adj[x].pb({y, i});
        adj[y].pb({x, i});
    }
    vector<int> vis(m + 1);
    auto        bfs = [&](int x) -> int {
        deque<int> que;
        int        cursz = 0;
        que.pb(x);
        while (!que.empty()) {
            int u = que.front();
            que.pop_front();
            for (auto [v, id] : adj[u]) {
                cursz++;
                if (!vis[v]) {
                    vis[v] = 1;
                    que.pb(v);
                }
            }
        }
        return cursz / 2;
    };
    bool                   ok = 1;
    vector<int>            dep(m + 1);
    vector<pair<int, int>> ans;
    auto                   dfs = [&](auto&& self, int u, int fa, int d = 1) -> int {
        dep[u] = d;
        vector<int> vec;
        int         faid;
        for (auto [v, id] : adj[u]) {
            if (v == fa) {
                faid = id;
                continue;
            }
            if (dep[v] > 0) {
                if (dep[v] < dep[u]) vec.push_back(id);
            } else {
                int t = self(self, v, u, d + 1);
                if (t > 0) vec.push_back(t);
            }
        }
        while (vec.size() > 1) {
            int x = vec.back();
            vec.pop_back();
            int y = vec.back();
            vec.pop_back();
            ans.push_back({x, y});
        }
        if (vec.size() == 1) {
            // 还剩一条边没匹配，把连向父节点的边也用来匹配
            assert(fa > 0);
            ans.push_back({vec.back(), faid});
            return -1;
        } else {
            // 连向父节点的边交给父节点匹配
            return faid;
        }
    };
    for (int i = 1; i <= m; i++) {
        if (!vis[i]) {
            vis[i]  = 1;
            int cnt = bfs(i);
            if (cnt % 2 != 0) {
                ok = 0;
                break;
            }
            dfs(dfs, i, 0);
        }
    }
    if (ok) {
        cout << "Yes\n";
        for (auto [u, v] : ans) {
            cout << u << ' ' << v << '\n';
        }
    } else {
        cout << "No\n";
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
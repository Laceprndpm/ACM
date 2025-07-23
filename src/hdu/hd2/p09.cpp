#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
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
vector<int>   tags;

template <class Info>
struct SegmentTree {
    int          n;
    vector<Info> info;

    SegmentTree() : n(0) {}

    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(vector(n_, v_));
    }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        assert(l <= r);
        return rangeQuery(1, 0, n, l, r);
    }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findLast(int l, int r, F &&pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int x;

    Info() : x(0) {}

    Info(int _x) : x(_x) {}
};

Info operator+(const Info &a, const Info &b)
{

    return {max(a.x, b.x)};
}

struct HLD {
    int                           n;
    std::vector<int>              siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int                           cur;

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
    }

    void dfs1(int u)
    {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }

        siz[u] = 1;
        for (auto &v : adj[u]) {
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

    int lca(int u, int v, SegmentTree<Info> &seg)
    {
        i64 ans = 0;
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                ans              = max<i64>(ans, seg.rangeQuery(in[top[u]], in[u] + 1).x);
                i64 raw_top_val  = seg.rangeQuery(in[top[u]], in[top[u]] + 1).x;
                i64 chain_parent = parent[top[u]];
                i64 top_val      = raw_top_val + tags[chain_parent];
                ans              = max<i64>(ans, top_val);
                u                = parent[top[u]];
            } else {
                ans              = max<i64>(ans, seg.rangeQuery(in[top[v]], in[v] + 1).x);
                i64 raw_top_val  = seg.rangeQuery(in[top[v]], in[top[v]] + 1).x;
                i64 chain_parent = parent[top[v]];
                i64 top_val      = raw_top_val + tags[chain_parent];
                ans              = max<i64>(ans, top_val);
                v                = parent[top[v]];
            }
        }
        if (dep[u] > dep[v]) {  // 让u是头
            swap(u, v);
        }
        if (u == top[u] && u != 0) {
            ans = max<i64>(ans, seg.rangeQuery(in[u], in[u] + 1).x + tags[parent[u]]);
        }
        ans = max<i64>(ans, seg.rangeQuery(in[u], in[v] + 1).x);
        return ans;
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
};

void solve()
{
    int n, m;
    cin >> n >> m;
    tags.assign(n, 0);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    HLD hld(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        hld.addEdge(u, v);
    }
    hld.work();
    const auto &in = hld.in;
    vector<int> dfs_ai(n);
    for (int i = 0; i < n; i++) {
        int place     = in[i];
        dfs_ai[place] = arr[i];
    }
    const auto &parrent = hld.parent;

    SegmentTree<Info> seg(dfs_ai);
    for (int i = 0; i < m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << hld.lca(u, v, seg) << '\n';
        } else {
            int x, z;

            cin >> x >> z;
            x--;
            if (x) {
                int pa_val = seg.rangeQuery(in[parrent[x]], in[parrent[x]] + 1).x;
                assert(in[parrent[x]] == in[x] - 1 || x == hld.top[x]);
                seg.modify(in[parrent[x]], pa_val + z);
            }
            if (hld.siz[x] > 1) {
                int son_seq = in[x] + 1;
                int son_val = seg.rangeQuery(son_seq, son_seq + 1).x;
                seg.modify(son_seq, {son_val + z});
            }
            tags[x] += z;
            //
            // 总之，我们有n条链
            // 假如，我修改它的重儿子，和他的父亲
            //
            //
        }
    }
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
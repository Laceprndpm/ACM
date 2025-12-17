#include <array>
#include <iostream>
#include <numeric>
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

/**
 * @brief 并查集
 * 0-index
 */

struct DSU {
    int              component;
    std::vector<int> f, siz;

    // embed
    DSU() {}

    DSU(int n) : component(n) { init(n); }

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

    std::vector<std::vector<int>> getGroups(void)
    {
        std::vector<std::vector<int>> res;
        std::vector<std::vector<int>> mp(f.size());
        for (int i = 0; i < (int)f.size(); i++) {
            mp[find(i)].emplace_back(i);
        }
        for (auto& group : mp) {
            if (group.empty()) continue;
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0) { init(n_); }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
    }

    void add(int x, const T& v)
    {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) { return sum(r) - sum(l); }

    int select(const T& k)
    {
        int x = 0;
        T   cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

template <class T>
struct RangeFenwick {
    int        n;
    Fenwick<T> d1, d2;

    RangeFenwick(int n_) : n(n_), d1(n_), d2(n_) {}

    void add(i64 k, T v)
    {
        T v1 = k * v;
        d1.add(k, v), d2.add(k, v1);
        // 在diff的k位置+v
    }

    void add(i64 l, i64 r, T v)
    {
        add(l, v), add(r, -v);  // 将区间加差分为两个前缀加
    }

    T getsum(i64 x) { return x * d1.sum(x) - d2.sum(x); }

    T getsum(i64 l, i64 r) { return getsum(r) - getsum(l); }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    DSU                            dsu(n + 1);
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int>                    par(n + 1);
    vector<int>                    pathxor(n + 1);
    vector<array<int, 20>>         mupar(n + 1);
    int                            cnt = 0;
    vector<int>                    in(n + 1), out(n + 1);
    vector<int>                    dep(n + 1);
    auto                           initlca = [&](void) {
        for (int u = 1; u <= n; u++) {
            mupar[u][0] = par[u];
        }
        for (int i = 1; i < 20; i++) {
            for (int j = 1; j <= n; j++) {
                mupar[j][i] = mupar[mupar[j][i - 1]][i - 1];
            }
        }
    };
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        for (int i = 19; i >= 0; i--) {
            if (dep[mupar[u][i]] >= dep[v]) {
                u = mupar[u][i];
            }
        }
        if (u == v) return u;
        for (int i = 19; i >= 0; i--) {
            if (mupar[u][i] != mupar[v][i]) {
                u = mupar[u][i];
                v = mupar[v][i];
            }
        }
        return par[u];
    };

    auto dfs = [&](this auto&& self, int u, int fa) -> void {
        in[u] = ++cnt;
        for (auto [v, w] : adj[u]) {
            if (v == fa) continue;
            par[v]     = u;
            dep[v]     = dep[u] + 1;
            pathxor[v] = pathxor[u] ^ w;
            self(v, u);
        }
        out[u] = cnt;
    };
    vector<int>           ans(q);
    vector<int>           tocheck;
    vector<array<int, 3>> query(q);
    for (int i = 0; i < q; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        query[i] = {u, v, x};
        if (!dsu.same(u, v)) {
            adj[u].pb({v, x});
            adj[v].pb({u, x});
            dsu.merge(u, v);
            ans[i] = 1;
        } else {
            tocheck.pb(i);
        }
    }
    vector<Fenwick<int>> fk(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i == dsu.find(i)) {
            cnt    = 0;
            fk[i]  = Fenwick<int>(dsu.size(i) + 2);
            par[i] = i;
            dep[i] = 1;
            dfs(i, 0);
        }
    }
    initlca();
    auto ad = [&](int root, int u, int v) -> void {
        if (dep[u] < dep[v]) {
            swap(u, v);
        }
        while (dep[u] != dep[v]) {
            fk[root].add(in[u], 1);
            fk[root].add(out[u] + 1, -1);
            u = par[u];
        }
        while (u != v) {
            fk[root].add(in[u], 1);
            fk[root].add(out[u] + 1, -1);
            fk[root].add(in[v], 1);
            fk[root].add(out[v] + 1, -1);
            u = par[u], v = par[v];
        }
        return;
    };
    for (int i : tocheck) {
        auto [u, v, x] = query[i];
        int root       = dsu.find(u);
        if ((pathxor[u] ^ pathxor[v] ^ x) != 1) continue;
        // cout << fk[root].sum(in[u] + 1) + fk[root].sum(in[v] + 1) - 2 * fk[root].sum(in[lca(u, v)] + 1) << endl;
        if (fk[root].sum(in[u] + 1) + fk[root].sum(in[v] + 1) - 2 * fk[root].sum(in[lca(u, v)] + 1) != 0) continue;
        ad(root, u, v);
        ans[i] = 1;
    }
    for (int i = 0; i < q; i++) {
        cout << (ans[i] ? "Yes\n" : "No\n");
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
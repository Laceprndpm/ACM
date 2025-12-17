#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include <set>
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

/**
 * @brief 并查集
 * 0-index
 */

struct DSU {
    int              component;
    std::vector<int> f, siz;

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
};

template <class Info>
struct SegmentTree {
    static int                   n;
    static vector<Info>          info;
    static vector<array<int, 2>> sons;
    static int                   cnt;
    int                          root;

    SegmentTree() { root = newnode(); }

    static void super_init(int n_)
    {
        n   = n_;
        cnt = 0;
        info.resize(1);
        sons.resize(1);
    }

    int newnode()
    {
        sons.pb({});
        info.pb({});
        return ++cnt;
    };

    bool empty() { return info[root].siz == 0; }

    void pull(int p) { info[p] = info[sons[p][0]] + info[sons[p][1]]; }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            if (sons[p][0] == 0) sons[p][0] = newnode();
            modify(sons[p][0], l, m, x, v);
        } else {
            if (sons[p][1] == 0) sons[p][1] = newnode();
            modify(sons[p][1], m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v) { modify(root, 0, n, p, v); }

    SegmentTree merges(SegmentTree &ot)
    {
        merge_impl(root, ot.root, 0, n);
        ot.root = 0;
        return *this;
    }

    int merge_impl(int u, int v, int l, int r)
    {
        if (!u) return v;
        if (!v) return u;
        if (r - l == 1) {
            info[u] = info[u] + info[v];
            // do something...
            return u;
        }
        int mid    = (l + r) >> 1;
        sons[u][0] = merge_impl(sons[u][0], sons[v][0], l, mid);
        sons[u][1] = merge_impl(sons[u][1], sons[v][1], mid, r);
        pull(u);
        return u;
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x || p == 0) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(sons[p][0], l, m, x, y) + rangeQuery(sons[p][1], m, r, x, y);
    }

    Info rangeQuery(int l, int r) { return rangeQuery(root, 0, n, l, r); }

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
        int res = findFirst(sons[p][0], l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(sons[p][1], m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(root, 0, n, l, r, pred);
    }
};

struct Info {
    int siz = 0;

    Info() {}

    Info(int _x) : siz(_x) {}
};

Info operator+(const Info &a, const Info &b)
{
    Info c;
    c.siz = a.siz + b.siz;
    return c;
}

template <class Info>
int SegmentTree<Info>::n = 0;

template <class Info>
std::vector<Info> SegmentTree<Info>::info;

template <class Info>
std::vector<std::array<int, 2>> SegmentTree<Info>::sons;

template <class Info>
int SegmentTree<Info>::cnt = 0;

void solve()
{
    i64 n, m;
    cin >> n >> m;
    SegmentTree<Info>::super_init(m + 1);
    vector<array<int, 3>>     edges(m + 1);
    vector<int>               idx(m + 1);
    vector<int>               deg(n + 1);
    i64                       ans = 0;
    vector<SegmentTree<Info>> nxtedge(n + 1);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        nxtedge[u].modify(i, {1});
        nxtedge[v].modify(i, {1});
        deg[u]++, deg[v]++;
        ans += w;
    }
    vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2) {
            cnt[i]++;
        }
    }
    iota(all(idx), 0);
    sort(idx.begin() + 1, idx.end(), [&](int a, int b) { return edges[a][2] < edges[b][2]; });
    DSU  dsu(n + 1);
    auto pred = [&](Info x) { return x.siz != 0; };
    for (int i = 1; i <= m; i++) {
        int curid = idx[i];
        int u     = edges[curid][0];
        int uid   = dsu.find(u);
        int res   = -1;
        while (!nxtedge[uid].empty() && (res = nxtedge[uid].findFirst(0, m + 1, pred)) <= curid) {
            auto [cu, cv, _] = edges[res];
            if (!dsu.same(u, cv)) {
                cnt[uid] += cnt[dsu.find(cv)];
                nxtedge[uid].merges(nxtedge[dsu.find(cv)]);
                dsu.merge(u, cv);
            }
            if (!dsu.same(u, cu)) {
                cnt[uid] += cnt[dsu.find(cu)];
                nxtedge[uid].merges(nxtedge[dsu.find(cu)]);
                dsu.merge(u, cu);
            }
            nxtedge[uid].modify(res, {0});
        }
        ans += cnt[uid] / 2ll * edges[curid][2];
        cnt[dsu.find(edges[curid][0])] %= 2;
    }
    cout << ans << '\n';
}

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
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
#include <bits/stdc++.h>

#include <functional>
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

constexpr i64 INF = 1e18;

struct Node {
    int u, l, r;
};

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
    i64 x, l = INF, ptr = 0;  // [8, 8], [10, 10]
};

Info operator+(const Info &a, const Info &b)
{
    if (a.l < b.l) {
        return a;
    } else {
        return b;
    }
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>         fa(n + 1);
    vector<vector<int>> child(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> fa[i];
        child[fa[i]].eb(i);
    }
    vector<Node> node(k);
    for (int i = 0; i < k; i++) {
        cin >> node[i].u >> node[i].l >> node[i].r;
    }
    vector<int>              in(n + 1);
    vector<int>              out(n + 1);
    int                      cur = -1;
    function<void(int, int)> dfs = [&](int u, int fa) -> void {
        in[u] = ++cur;
        for (int v : child[u]) {
            dfs(v, u);
        }
        out[u] = cur;
    };

    dfs(1, 1);
    vector<Info>                   seg_tmp(n);
    vector<vector<pair<int, int>>> dfsn_list(n);
    for (int i = 0; i < k; i++) {
        int dfsn = in[node[i].u];
        int l = node[i].l, r = node[i].r;
        dfsn_list[dfsn].pb({l, r});
    }

    for (int i = 0; i < n; i++) {
        if (dfsn_list[i].empty()) continue;
        seg_tmp[i] = {i, dfsn_list[i][0].fi, 0};
    }

    SegmentTree<Info> seg(seg_tmp);
    i64               ans = INF;

    function<void(int, int)> dfs2 = [&](int u, int cur_time) -> void {
        auto res = seg.rangeQuery(in[u], in[u] + 1);  // 用于特判root
        if (res.l != INF) {
            ans = min(ans, res.l);
        }
        for (int v : child[u]) {
            int  dfs_l = in[v], dfs_r = out[v] + 1;  // 作弊游客
            auto res            = seg.rangeQuery(dfs_l, dfs_r);
            auto [dfsn, l, ptr] = res;

            if (l == INF) {
                continue;
            }

            ans = min(ans, seg.rangeQuery(in[v], in[v] + 1).l);

            if (l == dfsn_list[dfsn][ptr].se) {
                if (ptr + 1 == sz(dfsn_list[dfsn])) {
                    seg.modify(res.x, {res.x, INF, INF});
                } else {
                    ptr++;
                    seg.modify(dfsn, {dfsn, dfsn_list[dfsn][ptr].fi, ptr});
                }
            } else {
                seg.modify(res.x, {res.x, l + 1, ptr});
            }

            dfs2(v, l + 1);
        }
    };
    dfs2(1, 0);
    cout << (ans == INF ? -1 : ans) << '\n';
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
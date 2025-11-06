#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
#define pb     push_back
#define bg(x)  begin(x)
#define all(x) bg(x), end(x)

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

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    u64 V;
    cin >> n >> m >> q >> V;
    DSU                          basic(n + 1);
    vector<tuple<int, int, u64>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        u64 w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        basic.merge(u, v);
    }
    vector<pair<int, int>> querys(q);
    vector<int>            ans(q);
    for (int j = 0, u, v; j < q; j++) {
        cin >> u >> v;
        querys[j] = {u, v};
    }
    for (int i = 60; i >= 0; i--) {
        DSU cur(n + 1);
        for (auto [u, v, w] : edges) {
            if (!(w & (1uLL << i)) || ((w & V) >> (i + 1)) != (V >> (i + 1))) continue;
            if (basic.same(u, v)) {
                cur.merge(u, v);
            }
        }
        if (V & (1uLL << i)) {
            basic = std::move(cur);
        } else {
            for (int j = 0; j < q; j++) {
                auto [u, v] = querys[j];
                if (cur.same(u, v)) {
                    ans[j] = 1;
                }
            }
        }
    }
    for (int j = 0; j < q; j++) {
        auto [u, v] = querys[j];
        if (basic.same(u, v)) {
            ans[j] = 1;
        }
    }
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}

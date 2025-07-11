#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF = 1e9;

/**
 * @brief 并查集
 * 0-index
 */
struct DSU {
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) : component(n)
    {
        init(n);
    }

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

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

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

    int size(int x)
    {
        return siz[find(x)];
    }

    std::vector<std::vector<int>> getGroups(void)
    {
        std::vector<std::vector<int>>   res;
        std::map<int, std::vector<int>> mp;
        for (int i = 0; i < f.size(); i++) {
            mp[find(i)].emplace_back(i);
        }
        res.reserve(mp.size());
        for (auto& [_, group] : mp) {
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    struct Edge {
        int u, v, cost;

        bool operator>(Edge& o)
        {
            return cost > o.cost;
        }
    };

    vector<Edge> edge(m);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edge[i] = {u, v, c};
    }
    sort(all(edge), greater<>());
    int q;
    cin >> q;
    vector<set<int>> query(n);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        query[u].insert(i);
        query[v].insert(i);
    }
    DSU         dsu(n);
    vector<i64> ans(q, -1);
    for (int i = 0; i < m; i++) {
        auto [u, v, c] = edge[i];
        if (dsu.same(u, v)) continue;
        u = dsu.find(u);
        v = dsu.find(v);
        if (query[u].size() < query[v].size()) {
            swap(u, v);
        }
        for (int i : query[v]) {
            if (query[u].contains(i)) {
                assert(ans[i] == -1);
                ans[i] = c;
            }
        }
        dsu.merge(u, v);
        query[u].insert(all(query[v]));
        query[v].clear();
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
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
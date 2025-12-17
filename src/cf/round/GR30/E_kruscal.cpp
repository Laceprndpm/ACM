#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> adj;
    vector<int>                  val(2 * n + 1, 1e9);
    DSU                          dsu(2 * n + 1);
    vector<int>                  siz(2 * n + 1);
    vector<int>                  deg(n + 1);
    i64                          ans = 0;
    int                          cnt = n;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        deg[u]++, deg[v]++;
        if (dsu.same(u, v)) {
            val[dsu.find(u)] = min(val[dsu.find(u)], w);
        } else {
            ++cnt;
            val[cnt] = w;
            adj.pb({cnt, dsu.find(u), dsu.find(v)});
            dsu.merge(cnt, u);
            dsu.merge(cnt, v);
        }
        ans += w;
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1) siz[i]++;
    }
    for (int i = n - 2; i >= 0; i--) {
        auto [rt, u, v] = adj[i];
        val[u]          = min(val[u], val[rt]);
        val[v]          = min(val[v], val[rt]);
    }
    for (int i = 0; i <= n - 2; i++) {
        auto [rt, u, v] = adj[i];
        siz[rt] += siz[u] + siz[v];
        ans += siz[rt] / 2ll * val[rt];
        siz[rt] = siz[rt] & 1;
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
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

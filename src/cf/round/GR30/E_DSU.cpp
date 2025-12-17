#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
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
    i64 n, m;
    cin >> n >> m;
    vector<array<int, 3>>                                                     edges(m + 1);
    vector<int>                                                               idx(m + 1);
    vector<int>                                                               deg(n + 1);
    i64                                                                       ans = 0;
    vector<priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>> nxtedge(n + 1);
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
        nxtedge[u].push({i, v});
        nxtedge[v].push({i, u});
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
    DSU dsu(n + 1);
    for (int i = 1; i <= m; i++) {
        int curid = idx[i];
        int u     = edges[curid][0];
        int uid   = dsu.find(u);
        while (!nxtedge[uid].empty() && nxtedge[uid].top().first <= curid) {
            auto [_, cv] = nxtedge[uid].top();
            // nxtedge[uid].erase(nxtedge[uid].begin());
            nxtedge[uid].pop();
            if (!dsu.same(u, cv)) {
                cnt[uid] += cnt[dsu.find(cv)];
                if (nxtedge[uid].size() < nxtedge[dsu.find(cv)].size()) swap(nxtedge[uid], nxtedge[dsu.find(cv)]);
                // nxtedge[uid].push_range(all(nxtedge[dsu.find(cv)]));
                while (!nxtedge[dsu.find(cv)].empty()) {
                    nxtedge[uid].push(nxtedge[dsu.find(cv)].top());
                    nxtedge[dsu.find(cv)].pop();
                }
                dsu.merge(u, cv);
            }
        }
        ans += cnt[uid] / 2ll * edges[curid][2];
        cnt[dsu.find(edges[curid][0])] %= 2;
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

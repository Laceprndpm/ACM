#include <algorithm>
#include <functional>
#include <iostream>
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

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> depth(n);
    vector<int> apD(n);
    vector<int> siz(n);

    auto dfs1 = [&](this auto&& dfs1, int u, int fa) -> void {
        siz[u] = 1;
        apD[depth[u]]++;
        for (int v : graph[u]) {
            if (v == fa) continue;
            depth[v] = depth[u] + 1;
            dfs1(v, u);
            siz[u] += siz[v];
        }
    };
    dfs1(0, 0);
    i64         ans1 = 0, ans2 = 0;
    vector<int> apDS = apD;
    for (int i = n - 2; i >= 0; i--) {
        apDS[i] += apDS[i + 1];
    }
    auto dfs2 = [&](this auto&& dfs2, int u, int fa) -> void {
        ans1 += 2 * depth[u] * 1ll * (apDS[depth[u]] - siz[u]);
        i64 cnt  = siz[u] - 1;
        i64 lcnt = 0;
        for (int v : graph[u]) {
            if (v == fa) continue;
            lcnt += 1ll * (cnt - siz[v]) * siz[v];
            dfs2(v, u);
        }
        ans2 += lcnt / 2ll * (depth[u] * 2 + 1);
    };
    dfs2(0, 0);
    for (i64 i = 0; i < n; i++) {
        ans1 -= apD[i] * 1ll * (apD[i] - 1) * i;
    }
    cout << ans1 - ans2 << '\n';
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
    // 考虑节点n的子树
    // a, b 的贡献是 a + b - abs(a - b) - 1
    // 贡献可以被拆解为 2 * min(a, b) - 1
    //
    //
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
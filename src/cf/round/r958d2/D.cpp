#include <array>
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

constexpr i64 INF      = 1e18;
constexpr int possible = 19;  // since __lg(3e5) == 19

void solve()
{
    int n;
    cin >> n;
    vector<array<i64, possible>> dp(n + 1);
    // vector<int>                  depth(n + 1);
    // i64                          ans1 = 0, ans2 = 0;
    vector<i64> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    vector<vector<int>> g(n + 1);
    // for (int i = 1; i < n; i++) {
    //     int u, v;
    //     cin >> u >> v;
    //     g[u].push_back(v);
    //     g[v].push_back(u);
    // }
    // auto dfs1 = [&](auto self, int u, int fa) -> void {
    //     ans1 += ai[u];
    //     ans2 += ai[u];
    //     if (depth[u] % 2 == 0) {
    //         ans2 += ai[u];
    //     } else {
    //         ans1 += ai[u];
    //     }
    //     for (int adj : g[u]) {
    //         if (adj == fa) continue;
    //         depth[adj] = depth[u] + 1;
    //         self(self, adj, u);
    //     }
    // };
    // dfs1(dfs1, 1, 1);
    auto dfs2 = [&](auto self, int u, int fa) -> void {
        for (int adj : g[u]) {
            if (adj == fa) continue;
            self(self, adj, u);
        }
        for (i64 i = 0; i < possible; i++) {
            dp[u][i] = (i + 1) * ai[u];
            for (int adj : g[u]) {
                if (adj == fa) continue;
                i64 curMin = INF;
                for (int j = 0; j < possible; j++) {
                    if (j == i) continue;
                    curMin = min(dp[adj][j], curMin);
                }
                dp[u][i] += curMin;
            }
        }
    };
    dfs2(dfs2, 1, 1);
    // i64 ans = min(ans1, ans2);
    i64 ans = INF;
    for (int i = 0; i < possible; i++) {
        ans = min(ans, dp[1][i]);
    }
    cout << ans << '\n';
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
    // possible way:
    // kill in 2 moves
    // only odds and even
    // kill in 3 moves
    // more choose, but must in 3 moves
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
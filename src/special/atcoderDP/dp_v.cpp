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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n, MOD;
    cin >> n >> MOD;
    vector<vector<int>> graph(n);
    for (i64 i = 1; i < n; i++) {
        i64 u, v;
        cin >> u >> v;
        --u, --v;
        graph[u].eb(v);
        graph[v].eb(u);
    }
    vector<i64> dp(n);

    auto dfs = [&](auto&& dfs, int u, int fa) -> void {
        dp[u] = 1;
        for (i64 v : graph[u]) {
            if (v == fa) continue;
            dfs(dfs, v, u);
            dp[u] = dp[u] * (dp[v] + 1) % MOD;
        }
        return;
    };
    dfs(dfs, 0, 0);
    vector<i64> ans(n);
    auto        dfs2 = [&](auto&& dfs2, int u, int fa, i64 faDP) -> void {
        ans[u]          = (faDP + 1) * dp[u] % MOD;
        int         siz = sz(graph[u]);
        vector<i64> prefix(siz + 1, 0);
        prefix[0] = 1;
        for (i64 i = 0; i < siz; i++) {
            if (graph[u][i] != fa) {
                prefix[i + 1] = prefix[i] * (dp[graph[u][i]] + 1ll) % MOD;
            } else {
                prefix[i + 1] = prefix[i];
            }
        }
        vector<i64> suffix(siz + 1, 0);
        suffix[siz] = 1;
        for (int i = siz - 1; i >= 0; i--) {
            if (graph[u][i] != fa) {
                suffix[i] = suffix[i + 1] * (dp[graph[u][i]] + 1ll) % MOD;
            } else {
                suffix[i] = suffix[i + 1];
            }
        }
        for (int i = 0; i < siz; i++) {
            if (graph[u][i] == fa) continue;
            dfs2(dfs2, graph[u][i], u, ((faDP + 1) * prefix[i] % MOD) * suffix[i + 1] % MOD);
        }
        return;
    };
    dfs2(dfs2, 0, 0, 0);
    for (int i = 0; i < n; i++) {
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
#include <bits/stdc++.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <functional>
#include <limits>
#include <vector>
using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()
#define pb(x)  push_back(x)
constexpr i64 INF = 1e16;

void solve()
{
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector<i64> cost(n + 1);
    cost[0] = 1e16;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    // 感觉倍增，因为必须清除掉手里的点，然后考虑跳到他的各级父亲
    vector<int>            parent(n + 1);
    vector<i64>            mincost = cost;
    vector<int>            depth(n + 1);
    array<vector<i64>, 20> dp;
    array<vector<int>, 20> logparent;
    for (int i = 0; i < 20; i++) {
        dp[i].resize(n + 1, 1e16);
        logparent[i].resize(n + 1);
    }
    // 3
    // 5 5
    // 1 2 3 4 5
    // 1 2
    // 1 3
    // 2 4
    // 2 5
    // 3 1
    // 2 1
    // 4 1
    // 5 1
    // 5 2
    //
    // 5 5
    // 1 5 1 1 1
    // 1 2
    // 1 3
    // 2 4
    // 2 5
    //
    // 3 1
    // 2 1
    // 4 1
    // 5 1
    // 2 5
    // 6 5
    // 9 9 8 2 4 4
    // 1 2
    // 1 3
    // 1 4
    // 1 5
    // 1 6
    // 2 1
    // 3 1
    // 4 1
    // 5 1
    // 6 1
    auto dfs = [&](this auto &&self, int u, int fa) -> void {
        for (int v : adj[u]) {
            if (v == fa) continue;
            logparent[0][v] = u;
            depth[v]        = depth[u] + 1;
            self(v, u);
        }
        sort(all(adj[u]), [&](int ida, int idb) {
            if (ida == fa) {
                return false;
            }
            if (idb == fa) {
                return true;
            }
            return mincost[ida] < mincost[idb];
        });
        if (adj[u].size() != 1) mincost[u] = min(mincost[u], mincost[adj[u][0]] + mincost[adj[u][1]]);
    };
    auto dfs2 = [&](this auto &&self, int u, int fa) -> void {
        for (int v : adj[u]) {
            if (v == fa) continue;
            if (v == adj[u][0]) {
                dp[0][v] = mincost[adj[u][1]];
            } else {
                dp[0][v] = mincost[adj[u][0]];
            }
            self(v, u);
        }
    };
    parent[0] = parent[1] = 0;
    depth[1]              = 1;
    dfs(1, 1);
    dfs2(1, 1);
    for (int i = 1; i < 20; i++) {
        for (int j = 1; j <= n; j++) {
            logparent[i][j] = logparent[i - 1][logparent[i - 1][j]];
            dp[i][j]        = dp[i - 1][j] + dp[i - 1][logparent[i - 1][j]];
        }
    }
    auto query = [&](int u, int v) -> i64 {
        i64 s = 0;
        for (int i = 19; i >= 0; i--) {
            if (depth[logparent[i][u]] >= depth[v]) {
                s += dp[i][u];
                u = logparent[i][u];
            }
        }
        if (u == v) {
            return s;
        } else {
            return -1;
        }
    };
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
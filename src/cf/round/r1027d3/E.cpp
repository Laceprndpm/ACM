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
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<vector<int>> g(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<i64> mxdp(n + 1);
    vector<i64> mndp(n + 1);

    vector<i64> dep(n + 1);
    auto        dfs = [&](auto self, int u, int fa) -> void {
        mxdp[u] = arr[u];
        mndp[u] = arr[u];
        if (dep[u] > 0) {
            mxdp[u] += max(-mndp[fa], 0ll);
            mndp[u] += min(-mxdp[fa], 0ll);
        }
        for (int adj : g[u]) {
            if (adj == fa) continue;
            dep[adj] = dep[u] + 1;
            self(self, adj, u);
        }
    };
    dfs(dfs, 1, 1);
    for (int i = 1; i <= n; i++) {
        cout << mxdp[i] << ' ';
    }
    cout << '\n';
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
#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, s;
    cin >> n >> s;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    vector<int> dist(n + 1, 0);
    vector<int> fa(n + 1);
    dist[1]                         = 1;
    int                      faridx = 1;
    vector<int>              vis(n + 1, false);
    function<void(int, int)> dfs = [&](int root, int last) {
        fa[root] = last;
        if (dist[root] > dist[faridx]) {
            faridx = root;
        }
        for (pair<int, int> iter : graph[root]) {
            if (iter.first == last || vis[iter.first]) continue;
            dist[iter.first] = dist[root] + iter.second;
            dfs(iter.first, root);
        }
    };
    dfs(1, 0);
    dist.resize(n + 1, 0);
    int A        = faridx;
    dist[faridx] = 0;
    dfs(faridx, 0);
    int B   = faridx;
    int ans = INF;
    fa[A]   = 0;
    for (int i = B, j = B; i; i = fa[i]) {
        while (dist[j] - dist[i] > s) {
            j = fa[j];
        }
        int x = max(dist[B] - dist[j], dist[i]);
        ans   = min(ans, x);
    }
    for (int i = B; i != 0; i = fa[i]) {
        dist[i] = 0;
        vis[i]  = true;
    }
    for (int i = B; i != 0; i = fa[i]) {
        dfs(i, fa[i]);
    }
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dist[i]);
    }
    cout << ans;
    return 0;
}
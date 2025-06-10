#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> lvec(n + 1), rvec(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> lvec[i] >> rvec[i];
    }
    vector<vector<int>> graph(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    vector<int>              ai(n + 1);
    i64                      ans = 0;
    function<void(int, int)> dfs = [&](int u, int fa) -> void {
        int mx = lvec[u];
        for (int adj : graph[u]) {
            if (adj == fa) continue;
            dfs(adj, u);
            mx = max(mx, ai[adj]);
        }
        ai[u] = min(mx, rvec[u]);
        for (int adj : graph[u]) {
            if (adj == fa) continue;
            ans += max(0, ai[adj] - ai[u]);
        }
    };
    dfs(1, 0);
    cout << ans + ai[1] << '\n';
    // deque<int> que;
    // int        lztTag = 0;
    // for (int i = 1; i <= n; i++) {
    //     if (degree[i] == 1) {
    //         que.push_back(i);
    //     }
    // }
    // int cur;
    // while (!que.empty()) {
    //     cur = que.front();
    //     que.pop_front();
    //     degree[cur] = 0;
    //     for (int adj : graph[cur]) {
    //         if (degree[adj] != 0) {
    //             int fa = adj;
    //             // lztTag += lztTag;
    //             if (lvec[cur] > lvec[fa]) {
    //                 int delta = max(lvec[cur] - rvec[fa], 0);
    //                 lvec[fa] += delta;
    //                 rvec[fa] += delta;
    //                 lztTag += delta;
    //             }
    //             degree[fa]--;
    //             if (degree[fa] == 1) {
    //                 que.push_back(fa);
    //             }
    //         }
    //     }
    // }
    // cout << lvec[cur] + lztTag << '\n';
}

signed main(int argc, char** argv)
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
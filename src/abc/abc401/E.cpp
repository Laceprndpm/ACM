#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
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
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool>                                vis(n + 1);
    vector<int>                                 removed(n + 1);
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i = 1; i <= n + 1; i++) {
        pq.push(i);
    }
    priority_queue<int, vector<int>, greater<>> candi;
    candi.push(1);
    vector<int>  ans(n + 1, INF);
    int          cnt = 0;
    vector<bool> already(n + 1, false);
    while (!candi.empty()) {
        int u = candi.top();
        candi.pop();
        vis[u] = true;
        cnt++;
        while (!pq.empty() && vis[pq.top()]) {
            pq.pop();
        }
        for (int adj : graph[u]) {
            if (!vis[adj] && !already[adj]) {
                candi.push(adj);
                already[adj] = true;
            }
        }
        if (pq.top() - 1 == cnt) ans[pq.top() - 1] = min((int)candi.size(), ans[pq.top() - 1]);
    }
    for (int i = 1; i <= n; i++) {
        if (ans[i] == INF) {
            cout << -1 << '\n';
        } else {
            cout << ans[i] << '\n';
        }
    }
    // dfs，优先返祖，每次选择返祖，需要移除所有相邻的
    // int cntmv = 0;
    // function<void(int)> dfs   = [&](int u) -> void {
    //     for (int i : graph[u]) {
    //         if (removed[i]++ == 0) {
    //             cntmv++;
    //         }
    //     }
    //     for (int i : graph[u]) {
    //         if (--removed[i] == 0) {
    //             cntmv--;
    //         }
    //     }
    // };

    return 0;
}
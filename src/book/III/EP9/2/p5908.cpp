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
    int n, d;
    cin >> n;
    cin >> d;

    Graph graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    vector<int>                        vis(n + 1);
    function<int(int root, int depth)> DFS = [&](int root, int depth) {
        int ans   = 1;
        vis[root] = true;
        if (depth >= d) return ans;
        for (int adj : graph[root]) {
            if (!vis[adj]) {
                ans += DFS(adj, depth + 1);
            }
        }
        return ans;
    };
    cout << DFS(1, 0) - 1;
    return 0;
}
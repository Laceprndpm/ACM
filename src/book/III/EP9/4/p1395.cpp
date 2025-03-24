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
    int n;
    cin >> n;
    vector<int> sonMax(n + 1);
    vector<int> sizeRoot(n + 1);
    Graph       graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    int center = 0;
    sonMax[0] = INF;
    function<void(int, int)> dfs    = [&](int root, int last) {
        sizeRoot[root] = 1, sonMax[root] = 0;
        for (int adj : graph[root]) {
            if (adj == last) continue;
            dfs(adj, root);
            sizeRoot[root] += sizeRoot[adj];
            sonMax[root] = max(sonMax[root], sizeRoot[adj]);
        }
        sonMax[root] = max(sonMax[root], n - sizeRoot[root]);
        if (sonMax[root] < sonMax[center] || (sonMax[root] == sonMax[center] && root < center)) {
            center = root;
        }
    };
    dfs(1, 0);
    cout << center << ' ';
    function<int(int root)> bfs = [&](int root) {
        vector<int> depth(n + 1, 0);
        queue<int>  q;
        int         sum = 0;
        q.emplace(root);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int adj : graph[cur]) {
                if (depth[adj] != 0 || adj == root) continue;
                depth[adj] = depth[cur] + 1;
                sum += depth[adj];
                q.emplace(adj);
            }
        }
        return sum;
    };
    int ans = bfs(center);
    cout << ans;
    return 0;
}
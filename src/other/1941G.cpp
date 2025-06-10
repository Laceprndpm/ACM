#include <bits/stdc++.h>
using namespace std;
using i64                          = long long;
using PII                          = pair<int, int>;
constexpr int                  INF = 1e9;
vector<vector<pair<int, int>>> graph;
int                            b, e;
deque<pair<int, int>>          q;
int                            n, m;

int BFS()
{
    vector<int> dist(n, INF);
    dist[b] = 0;
    q.emplace_back(b, 0);
    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop_front();
        int root = cur.first;
        int last = cur.second;
        for (pair<int, int> adj : graph[root]) {
            if (adj.second == last) {
                q.emplace_front(adj.first, adj.second);
                dist[adj.first] = min(dist[root], dist[adj.first]);
            } else {
                q.emplace_back(adj.first, adj.second);
                dist[adj.first] = min(dist[root] + 1, dist[adj.first]);
            }
        }
    }
    return dist[e];
}

void solve()
{
    cin >> n >> m;
    graph.clear();
    graph.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, color;
        cin >> u >> v >> color;
        u--, v--;
        graph[u].emplace_back(v, color);
        graph[v].emplace_back(u, color);
    }
    cin >> b >> e;
    b--, e--;
    cout << BFS() << '\n';
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
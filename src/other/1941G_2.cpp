#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           n, m;

int BFS01(const vector<vector<pair<int, int>>>& graph, int b, int e)
{
    vector<int> dist(graph.size(), INF);
    deque<int>  q;
    dist[b] = 0;
    q.emplace_back(b);
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        for (pair<int, int> adj : graph[cur]) {
            if (dist[adj.first] == INF) {
                if (adj.second == 0) {
                    q.emplace_front(adj.first);
                    dist[adj.first] = dist[cur];
                } else {
                    q.emplace_back(adj.first);
                    dist[adj.first] = dist[cur] + 1;
                }
            }
        }
    }
    return dist[e];
}

void solve()
{
    int b, e;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + m + 50);
    map<int, int>                  colorset;
    int                            w = 1;
    for (int i = 0; i < m; i++) {
        int u, v, color;
        cin >> u >> v >> color;
        u--, v--;
        if (!colorset.count(color)) {
            colorset[color] = w;
            w++;
        }
        int colornode = colorset[color] + n;
        graph[u].emplace_back(colornode, 0);
        graph[v].emplace_back(colornode, 0);
        graph[colornode].emplace_back(u, 1);
        graph[colornode].emplace_back(v, 1);
    }
    cin >> b >> e;
    b--, e--;
    cout << BFS01(graph, b, e) << '\n';
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
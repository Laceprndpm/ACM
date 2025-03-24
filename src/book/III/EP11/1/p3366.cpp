#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

class Prim {
private:
    const vector<vector<pair<int, int>>>& originGraph;
    const int                             n;
    vector<int>                           dist;
    vector<int>                           father;
    vector<vector<pair<int, int>>>        treegraph;
    i64                                   totalLength = 0;
    bool                                  _canBuild;

    void build()
    {
        vector<bool>                                                      vis(n + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        int                                                               cnt = 0;
        pq.push({0, 1});
        dist[1] = 0;
        while (!pq.empty()) {
            pair<int, int> cur = pq.top();
            pq.pop();
            int idx = cur.second;
            if (vis[idx]) continue;
            cnt++;
            totalLength += dist[idx];
            vis[idx] = true;
            for (pair<int, int> adj : originGraph[idx]) {
                int v = adj.first;
                int w = adj.second;
                if (dist[v] > w) {
                    father[v] = idx;
                    dist[v]   = w;
                    pq.push({w, v});
                }
            }
        }
        if (cnt < n) {
            _canBuild = false;
            return;
        } else {
            _canBuild = true;
        }
        for (int i = 2; i <= n; i++) {
            treegraph[father[i]].emplace_back(i, dist[i]);
            treegraph[i].emplace_back(father[i], dist[i]);
        }
    }

public:
    Prim(const vector<vector<pair<int, int>>>& graph)
        : originGraph(graph), n(originGraph.size() - 1), dist(n + 1, INF), father(n + 1), treegraph(n + 1)
    {
        build();
    }

    bool canBuild()
    {
        return _canBuild;
    }

    i64 getTotalLength()
    {
        if (!_canBuild) {
            throw runtime_error("Can not!");
        }
        return totalLength;
    }

    vector<vector<pair<int, int>>> getTreeGraph()
    {
        return treegraph;
    }
};

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
    using Graph = vector<vector<pair<int, int>>>;
    Graph graph(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }
    Prim prim(graph);
    if (!prim.canBuild()) {
        cout << "orz";
    } else {
        cout << prim.getTotalLength();
    }
    return 0;
}
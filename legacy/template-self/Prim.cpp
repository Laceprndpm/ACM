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

// OI-wiki的最小生成树疑似有误，重构后给出新的代码
// 只需要将greater<>改为less<>即是最大生成树

/**
 * @version 2.0
 * @author laceprndpm
 * @date 2025/7/11
 */

pair<vector<vector<pair<int, int>>>, i64> primMST(const vector<vector<pair<int, int>>>& graph)
{
    i64                                                             len = 0;
    int                                                             n   = graph.size() - 1;
    vector<vector<pair<int, int>>>                                  treegraph(n + 1);
    vector<bool>                                                    vis(n + 1);
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;

    for (int u_i = 1; u_i <= n; ++u_i) {
        if (vis[u_i]) continue;
        vis[u_i] = true;
        for (auto [v, w] : graph[u_i]) {
            pq.push({w, u_i, v});
        }
        while (!pq.empty()) {
            auto [d, u, v] = pq.top();
            pq.pop();
            if (vis[v]) continue;
            vis[v] = true;
            len += d;
            treegraph[u].emplace_back(v, d);
            treegraph[v].emplace_back(u, d);
            for (auto [vv, w] : graph[v]) {
                pq.push({w, v, vv});
            }
        }
    }

    return {treegraph, len};
}

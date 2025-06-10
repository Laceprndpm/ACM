#ifndef REMOVE_ME
#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
constexpr int INF = 1e9;
#endif

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


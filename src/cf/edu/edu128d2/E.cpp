#include <queue>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
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

void solve()
{
    int m;
    cin >> m;
    string up, down;
    cin >> up;
    cin >> down;
    i64 needfill;
    int last     = 0;
    int lastlast = 0;
    for (int i = 0; i < m; i++) {
        if (up[i] == '*' || down[i] == '*') {
            if (up[i] == '*' && down[i] == '*') {
                lastlast = last;
                last     = 3;
            } else if (up[i] == '*') {
                if (last == 2 && lastlast == 1) {
                    up[needfill] = '*';
                }
                lastlast = last;
                last     = 1;
                needfill = i;
            } else if (down[i] == '*') {
                if (last == 1 && lastlast == 2) {
                    down[needfill] = '*';
                }
                lastlast = last;
                last     = 2;
                needfill = i;
            }
        }
    }
    int                            u = -1, d = -1;
    int                            uidx = -1, didx = 0;
    vector<vector<pair<int, int>>> graph(1);
    int                            cnt = -1;
    for (int i = 0; i < m; i++) {
        if (up[i] == '*') {
            cnt++;
            graph.emplace_back();
            if (u != -1) {
                graph[cnt].emplace_back(uidx, i - u);
                graph[uidx].emplace_back(cnt, i - u);
            }
            if (d != -1) {
                graph[cnt].emplace_back(didx, i - d + 1);
                graph[didx].emplace_back(cnt, i - d + 1);
            }
            u    = i;
            uidx = cnt;
        }
        if (down[i] == '*') {
            cnt++;
            graph.emplace_back();
            if (d != -1) {
                graph[cnt].emplace_back(didx, i - d);
                graph[didx].emplace_back(cnt, i - d);
            }
            if (u != -1) {
                graph[cnt].emplace_back(uidx, i - u + 1);
                graph[uidx].emplace_back(cnt, i - u + 1);
            }
            d    = i;
            didx = cnt;
        }
        if (up[i] == '*' && down[i] == '*') {
            graph[uidx].emplace_back(didx, 1);
            graph[didx].emplace_back(uidx, 1);
        }
    }
    Prim p(graph);
    cout << p.getTotalLength() << '\n';
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
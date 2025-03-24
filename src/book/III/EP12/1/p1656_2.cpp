#include <bits/stdc++.h>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
vector<vector<int>> graph;

vector<pair<int, int>> ans;

int dfn[151], low[151], n, m, id, cnt, father[151];

void myDFS(int root)
{
    dfn[root] = low[root] = ++id;
    for (int& adj : graph[root]) {
        if (dfn[adj] && adj != father[root]) {
            low[root] = min(dfn[adj], low[root]);
        }
        if (!dfn[adj]) {
            father[adj] = root;
            myDFS(adj);
            low[root] = min(low[root], low[adj]);

            if (low[adj] > dfn[root]) {
                if (root > adj) {
                    ans.emplace_back(adj, root);
                } else {
                    ans.emplace_back(root, adj);
                }
            }
        }
    }
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
    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    myDFS(1);
    sort(ans.begin(), ans.end());
    for (pair<int, int>& i : ans) {
        cout << i.first << ' ' << i.second << '\n';
    }
    return 0;
}
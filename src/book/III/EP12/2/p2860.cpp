#include <bits/stdc++.h>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
vector<vector<int>> graph;

vector<pair<int, int>> ans;

int dfn[5005], low[5005], n, m, id, cnt, father[5005], stackDFS[5005], top, bel[5005];

void myDFS(int root)
{
    dfn[root] = low[root] = ++id;
    stackDFS[++top]       = root;
    for (int& adj : graph[root]) {
        if (dfn[adj] && adj != father[root]) {
            low[root] = min(dfn[adj], low[root]);
        }
        if (!dfn[adj]) {
            father[adj] = root;
            myDFS(adj);
            low[root] = min(low[root], low[adj]);

            if (low[adj] > dfn[root]) {
                ans.emplace_back(root, adj);
            }
        }
    }
    if (low[root] == dfn[root]) {
        int v;
        ++cnt;
        do {
            v      = stackDFS[top--];
            bel[v] = cnt;
        } while (v != root);
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
    graph.resize(n + 5);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    myDFS(1);
    vector<int> degree(n + 5, 0);
    for (pair<int, int>& i : ans) {
        degree[bel[i.first]]++;
        degree[bel[i.second]]++;
    }
    int cntLeaves = 0;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            cntLeaves++;
        }
    }
    if (cntLeaves != 0)
        cout << (cntLeaves - 1) / 2 + 1;
    else
        cout << 0;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

vector<int>         ans;
vector<vector<int>> graph;

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

            // if (low[adj] > dfn[root]) {
            //     ans.emplace_back(root, adj);
            // }
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

    return 0;
}
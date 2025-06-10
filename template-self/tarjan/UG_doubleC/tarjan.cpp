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

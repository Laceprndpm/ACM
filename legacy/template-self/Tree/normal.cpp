const vector<int> dfssize(const vector<vector<int>>& graph, const int root)
{
    vector<int>              sz(graph.size());
    function<void(int, int)> dfs = [&](int cur, int fa) -> void {
        sz[cur] = 1;
        for (int i : graph[cur]) {
            if (i == fa) continue;
            dfs(i, cur);
            sz[cur] += sz[i];
        }
    };
    dfs(root, -1);
    return sz;
}

vector<int> getGraphWeightCenter(const vector<vector<int>>& graph)
{
    auto                     sz     = dfssize(graph, 1);
    int                      curMin = graph.size();
    vector<int>              maxv(graph.size());
    vector<int>              center;
    function<void(int, int)> dfs = [&](int cur, int father) -> void {
        maxv[cur] = sz[1] - sz[cur];
        for (int i : graph[cur]) {
            maxv[cur] = max(maxv[cur], sz[i]);
            dfs(i, cur);
        }
        if (curMin > maxv[cur]) {
            curMin = maxv[cur];
            center = vector<int>{cur};
        } else if (curMin == maxv[cur]) {
            center.push_back(cur);
        }
    };
    return center;
}
struct Hungary {
private:
    int                 totalNum;  // 传入总的点数
    int                 leftNum;   // 左边去和别人配对的点
    int                 maxMatch;
    vector<vector<int>> adj;
    vector<int>         match;
    vector<int>         vis;
    int                 op;

public:
    void init(int _totalNum, int _leftNum)
    {
        op       = 0;
        totalNum = _totalNum;
        leftNum  = _leftNum;
        maxMatch = 0;
        adj.assign(totalNum, {});
        match.assign(totalNum, -1);
        vis.assign(totalNum, -1);
    }

    void clear()
    {
        op       = 0;
        maxMatch = 0;
        vis.assign(totalNum, -1);
        match.assign(totalNum, -1);
    }

    Hungary() {}

    Hungary(int _totalNum, int _leftNum) { init(_totalNum, _leftNum); }

    void addEdge(int u, int v) { adj[u].push_back(v); }

    bool dfs(int cur)
    {
        if (vis[cur] == op) return false;
        vis[cur] = op;
        for (int x : adj[cur]) {
            if (match[x] == -1 || dfs(match[x])) {
                match[x] = cur;
                return true;
            }
        }
        return false;
    }

    int work()
    {
        for (int i = 0; i < leftNum; i++) {
            op = i;
            if (dfs(i)) {
                maxMatch++;
            }
        }
        return maxMatch;
    }

    vector<std::pair<int, int>> getMatch()
    {
        vector<std::pair<int, int>> exactmatch;
        for (int i = 0; i < totalNum; i++) {
            if (match[i]) {
                exactmatch.push_back({match[i], i});
            }
        }
        return exactmatch;
    }
};

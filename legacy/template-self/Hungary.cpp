
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Hungary {
private:
    int                 totalNum;  // 传入总的点数
    int                 leftNum;   // 左边去和别人配对的点
    int                 Maxedge;
    bool                worked = false;
    vector<vector<int>> adj;
    vector<int>         match;
    vector<int>         vis;

    bool dfs(int cur, int op)
    {
        if (vis[cur] == op) return false;
        vis[cur] = op;
        for (int x : adj[cur]) {
            if (!match[x] || dfs(match[x], op)) {
                match[x] = cur;
                return true;
            }
        }
        return false;
    }

public:
    Hungary(int _leftNum, int _rightNum) : leftNum(_leftNum), totalNum(_leftNum + _rightNum)
    {
        Maxedge = 0;
        adj.assign(totalNum + 1, {});
        match.assign(totalNum + 1, 0);
        vis.assign(totalNum + 1, 0);
    }

    void addedge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void work()
    {
        for (int i = 1; i <= leftNum; i++) {
            if (dfs(i, i)) {
                Maxedge++;
            }
        }
        worked = true;
    }

    int getMaxedge()
    {
        assert(worked);
        return Maxedge;
    }

    vector<std::pair<i64, i64>> getExatctlyMatch()
    {
        assert(worked);
        vector<std::pair<i64, i64>> exactmatch;
        for (int i = 1; i <= totalNum; i++) {
            if (match[i]) {
                exactmatch.push_back({match[i], i});
            }
        }
        return exactmatch;
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

    return 0;
}
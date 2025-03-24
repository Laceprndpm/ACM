#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

struct edge {
    int u, w;
};

int                  n;
vector<vector<edge>> g;
vector<vector<int>>  nextGraphNodes;
vector<int>          timeIn, timeOut, siz, ord;
int                  T;

vector<int> pathWeights;

// DFS初始化，计算时间戳、子树大小、遍历顺序
void init(int v, int p = -1)
{
    timeIn[v] = T++;
    ord.push_back(v);
    siz[v] = 1;
    for (const auto &it : g[v]) {
        int u = it.u, w = it.w;
        if (u == p) continue;
        pathWeights[u] = w;  // 记录u到父节点v的边颜色
        init(u, v);
        siz[v] += siz[u];  // 累加子树大小
    }
    timeOut[v] = T;  // 离开时间戳
}

int isAncestor(int v, int u)
{
    return timeIn[v] <= timeIn[u] && timeOut[v] >= timeOut[u];
}

vector<int> dp;

long long dfs(int v, int x)
{
    long long res = 0;
    for (int u : nextGraphNodes[v])
        res += dfs(u, x);
    dp[v] = siz[v];
    for (int u : nextGraphNodes[v])
        dp[v] -= siz[u];
    for (int u : nextGraphNodes[v]) {
        res += dp[u] * 1ll * dp[v];
    }
    return res;
}

int main()
{
    scanf("%d", &n);

    g.resize(n);
    forn(i, n - 1)
    {
        int v, u, w;
        scanf("%d%d%d", &v, &u, &w);
        --v, --u, --w;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }

    T = 0;
    timeIn.resize(n);
    timeOut.resize(n);
    siz.resize(n);
    pathWeights.resize(n, -1);
    init(0);

    vector<vector<int>> sv(n, vector<int>(1, 0));
    for (int v : ord)
        // for (auto it : g[v])
        //     sv[it.w].push_back(v);
        if (v != 0) sv[pathWeights[v]].emplace_back(v);

    nextGraphNodes.resize(n);
    dp.resize(n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (!sv[i].empty()) {
            // sv[i].erase(unique(sv[i].begin(), sv[i].end()), sv[i].end());
            vector<int> st;  // 栈维护当前链
            for (int v : sv[i]) {
                while (!st.empty() && !isAncestor(st.back(), v))
                    st.pop_back();
                if (!st.empty()) nextGraphNodes[st.back()].push_back(v);
                st.push_back(v);
            }
            ans += dfs(0, i);

            // for (int v : sv[i])
            nextGraphNodes[0].clear();
        }
    }

    printf("%lld\n", ans);
    return 0;
}
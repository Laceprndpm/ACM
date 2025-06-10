#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

struct edge {
    int u, w;  // 边的终点和权重（颜色）
};

int                  n;
vector<vector<edge>> g;                    // 邻接表表示的树
vector<vector<int>>  ng;                   // 虚树的邻接表
vector<int>          tin, tout, siz, ord;  // DFS时间戳、子树大小、遍历顺序
int                  T;                    // 时间戳计数器
vector<int>          pw;                   // 每个节点到父节点的边颜色

// DFS初始化，计算时间戳、子树大小、遍历顺序
void init(int v, int p = -1)
{
    tin[v] = T++;
    ord.push_back(v);
    siz[v] = 1;
    for (const auto &it : g[v]) {
        int u = it.u, w = it.w;
        if (u == p) continue;
        pw[u] = w;  // 记录u到父节点v的边颜色
        init(u, v);
        siz[v] += siz[u];  // 累加子树大小
    }
    tout[v] = T;  // 离开时间戳
}

// 判断v是否是u的祖先
int isAncestor(int v, int u)
{
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

vector<vector<int>> dp;  // DP数组，dp[v][0]和dp[v][1]表示不同状态

// 在虚树上动态规划，计算颜色x的路径数目
long long dfs(int v, int x)
{
    long long res = 0;
    for (int u : ng[v])  // 处理所有子节点
        res += dfs(u, x);

    // 初始化：当前节点v的初始状态
    dp[v][0] = siz[v];  // 初始为子树大小
    dp[v][1] = 0;       // 另一状态初始为0

    // 减去子节点对应子树的大小（虚树中的子节点）
    for (int u : ng[v])
        dp[v][0] -= siz[u];

    // 处理每个子节点u
    for (int u : ng[v]) {
        if (pw[u] == x) {  // 子节点u的边颜色为x
            // 路径组合：u的路径与当前路径连接
            res += dp[u][0] * dp[v][0];
            dp[v][1] += dp[u][0];  // 更新状态1
        } else {
            // 非x颜色边，组合两种状态的路径
            res += dp[u][0] * dp[v][1];
            res += dp[u][1] * dp[v][0];
            dp[v][0] += dp[u][0];  // 合并状态0
            dp[v][1] += dp[u][1];  // 合并状态1
        }
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
        --v, --u, --w;  // 转换为0-based索引
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }

    // 初始化各数组
    T = 0;
    tin.resize(n);
    tout.resize(n);
    siz.resize(n);
    pw.resize(n, -1);
    init(0);  // 从根节点0开始DFS初始化

    // 按颜色分组，收集所有相关节点
    vector<vector<int>> sv(n, vector<int>(1, 0));  // 初始包含根节点
    for (int v : ord) {
        for (auto it : g[v]) {
            int w = it.w;
            sv[w].push_back(it.u);  // 将边颜色为w的节点加入对应列表
        }
    }

    // 构建虚树并进行动态规划
    ng.resize(n);
    dp.resize(n, vector<int>(2));
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (!sv[i].empty()) {
            // 去重并排序节点（按DFS序）
            sort(sv[i].begin(), sv[i].end());
            sv[i].erase(unique(sv[i].begin(), sv[i].end()), sv[i].end());
            sort(sv[i].begin(), sv[i].end(), [&](int a, int b) {
                return tin[a] < tin[b];
            });

            // 构建虚树
            vector<int> st;  // 栈维护当前链
            for (int v : sv[i]) {
                while (!st.empty() && !isAncestor(st.back(), v))
                    st.pop_back();
                if (!st.empty()) ng[st.back()].push_back(v);  // 添加虚树边
                st.push_back(v);
            }

            // 计算颜色i的路径数目并累加
            ans += dfs(0, i);

            // 清空虚树邻接表
            for (int v : sv[i])
                ng[v].clear();
        }
    }

    printf("%lld\n", ans);
    return 0;
}
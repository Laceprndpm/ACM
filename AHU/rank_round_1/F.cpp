#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

struct SCC {
    int                           n;
    std::vector<std::vector<int>> adj;
    std::vector<int>              stk;
    std::vector<int>              dfn, low, bel;
    int                           cur, cnt;

    SCC() {}

    SCC(int n)
    {
        init(n);
    }

    void init(int n)
    {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void dfs(int x)
    {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);

        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

        if (dfn[x] == low[x]) {
            int y;
            do {
                y      = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }

    std::vector<int> work()
    {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
        return bel;
    }
};

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m, h;
    cin >> n >> m >> h;
    vector<int> urr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> urr[i];  // i-idx
    }
    SCC                 g(n + 1);
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;  // 1-idx
        for (int j = 0; j < 2; j++) {
            if ((urr[u] + 1) % h == urr[v]) {  // 该点+1将导致其子节点+1
                g.addEdge(u, v);               // u->v
                graph[u].push_back(v);         // u->v
            }
            swap(u, v);  // swap
        }
    }
    vector<int>         res = g.work();  // work
    vector<vector<int>> dfs_vec(n + 1);  // 每个dfsn对应哪些点？
    vector<set<int>>    n_graph(n + 1);  // 新图
    // 我现在有原始图，缩点后每个点对应的dfsn序
    // 先把所有原点挂载到dfsn序上，然后dfsn序上跑dfs?
    vector<int> ok(n + 1);
    for (int i = 1; i <= n; i++) {
        dfs_vec[res[i]].push_back(i);  // 挂载到dfsn节点上
        ok[res[i]] = 1;                // 嗯，这个连通块是存在的
        auto tmp   = graph[i];         // 这个点所有的出口
        for (int& j : tmp) {           // 转换成连通块
            j = res[j];
        }
        n_graph[res[i]].insert(all(tmp));  // 重新插入
    }
    vector<int> siz_dfsn(n + 1, INF);  // 初始化为INF
    vector<int> vis(n + 1);            // 是否来过
    // auto        dfs = [&](auto self, int u, int fa) -> int {
    //     if (vis[u])
    //         return siz_dfsn[u];  // 如果来过了，直接return
    //                              // 这个连通块的大小是否。。无环，，，
    //                              // 是否代表。。。哦，不过答案应该只会在根出现吧
    //     // 1->2, 1->3
    //     // 2->3的情况
    //     siz_dfsn[u] = sz(dfs_vec[u]);  // 自己这个连通块
    //     vis[u]      = 1;
    //     for (int adj : n_graph[u]) {  // DAG
    //         if (adj == u) continue;   // 有自环的DAG
    //         siz_dfsn[u] += self(self, adj, u);
    //     }
    //     return siz_dfsn[u];
    // };
    int mnidx   = 1;
    siz_dfsn[0] = INF;
    for (int i = 1; i <= n; i++) {  // dfsn总不可能大于n吧？
        if (!ok[i]) continue;
        if (n_graph[i].contains(i)) {
            n_graph[i].erase(i);
        }
        // if (!vis[i] && sz(dfs_vec[i])) {
        //     dfs(dfs, i, 0);
        // }
        // if (sz(n_graph[i]) == 0 && sz(dfs_vec[i]) && (siz_dfsn[mnidx] > siz_dfsn[i])) {  // 不为空即有效
        //     mnidx = i;
        // }
        if (sz(n_graph[i]) == 0 && sz(dfs_vec[i]) && (sz(dfs_vec[mnidx]) > sz(dfs_vec[i]))) {  // 不为空即有效
            mnidx = i;
        }
    }
    cout << sz(dfs_vec[mnidx]) << '\n';
    for (int i : dfs_vec[mnidx]) {
        cout << i << ' ';
    }
    虽然很神秘
    // int idx = 1;
    // for (int i = 1; i <= n; i++) {
    //     // if (w[i] == 0) continue;
    //     // if (w[g.dfn[i]] < w[g.dfn[idx]]) {
    //     //     idx = i;
    //     // }
    // }
    // cout << idx << '\n';
    // cout << w[g.dfn[idx]] << '\n';
    //
    // 也许dsu
    // 如果
    // 有向图
    // 有向图上找最小连通块子树？如果成环就缩点？
    // 二分肯定不行
    //
    // 如果u,v有通路，那么每次尝试改变u，如果v和它相同了，就也要改变v
    // 既然有解，大概率不会自环吧，而且如果所有时间都偏移，一定有解
    //
    //
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
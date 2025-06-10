#include <functional>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
#define int long long
constexpr int INF = 1e18;

tuple<vector<int>, vector<int>, vector<int>, vector<int>> markDFSorder(vector<vector<pair<int, int>>>& graph)
{
    vector<int>              dfsorder(graph.size());
    vector<int>              depth_DFSo(graph.size());
    vector<int>              father(graph.size());
    vector<int>              minn(graph.size());
    int                      cnt = 0;
    function<void(int, int)> dfs = [&](int u, int dep) -> void {
        dfsorder[u]     = ++cnt;
        depth_DFSo[cnt] = dep;
        for (const auto& [adj, w] : graph[u]) {
            if (dfsorder[adj] == 0) {
                father[adj] = u;
                minn[adj]   = min(minn[u], w);
                dfs(adj, dep + 1);
            }
        }
    };
    minn[1] = INF;
    dfs(1, 0);
    return {dfsorder, depth_DFSo, father, minn};
}

class LCA {
    int                 n;
    vector<vector<int>> stTable;
    const vector<int>&  depth_DFSo;
    const vector<int>&  dfsorder;
    const vector<int>&  father;
    vector<int>         ndfs;

    int lowbit_cnt(int x)
    {
        int i   = x & -x;
        int cnt = 0;
        while (i) {
            i >>= 1;
            cnt++;
        }
        return cnt - 1;
    }

    int get(int u, int v)
    {
        if (depth_DFSo[u] < depth_DFSo[v]) {
            return u;
        } else {
            return v;
        }
    }

    int queryST(int l, int r)
    {
        int ans = stTable[l][0];
        while (l < r) {
            int j = lowbit_cnt(r - l);
            ans   = get(ans, stTable[l][j]);
            l += 1 << j;
        }
        return ans;
    }

public:
    LCA(const vector<int>& dfsorder, const vector<int>& depth_, const vector<int>& father_)
        : n(dfsorder.size() - 1),
          stTable(n + 1, vector<int>(__lg(n) + 1)),
          depth_DFSo(depth_),
          dfsorder(dfsorder),
          father(father_),
          ndfs(n + 1)
    {
        for (int i = 1; i <= n; i++) {
            ndfs[dfsorder[i]] = i;
        }
        for (int i = 1; i <= n; i++) {
            stTable[i][0] = i;
        }
        for (int j = 1; j <= __lg(n); j++) {
            for (int i = 1; i <= n - (1 << (j - 1)); i++) {
                stTable[i][j] = get(stTable[i][j - 1], stTable[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int getLCA(int u, int v)
    {
        if (u == v) {
            return u;
        }
        int l = dfsorder[u], r = dfsorder[v];
        int ans_dfso = queryST(min(l, r) + 1, max(l, r) + 1);
        return father[ndfs[ans_dfso]];
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
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    const auto&& [dfsOrder, depth, father, minn] = markDFSorder(graph);
    LCA lca(dfsOrder, depth, father);
    int q;
    cin >> q;
    vector<vector<int>>      virtualTree(n + 1);
    vector<int>              sta(n + 5);
    int                      top = 0;
    function<bool(int, int)> cmp = [&](int a, int b) -> bool {
        return dfsOrder[a] < dfsOrder[b];
    };
    vector<int>           dp(n + 1);
    set<int>              critical;
    function<void(int u)> dfs = [&](int u) -> void {
        dp[u] = 0;
        for (int i : virtualTree[u]) {
            dfs(i);
            if (critical.count(i) != 0) {
                dp[u] = dp[u] + minn[i];
            } else {
                dp[u] = dp[u] + min(dp[i], minn[i]);
            }
        }
    };
    while (q--) {
        virtualTree[1].clear();
        sta[0] = 1;
        top    = 1;
        int k;
        cin >> k;
        vector<int> h(k);
        for (int i = 0; i < k; i++) {
            cin >> h[i];
        }
        sort(h.begin(), h.end(), cmp);
        critical = set<int>(h.begin(), h.end());
        for (int i = 0; i < k; i++) {
            int l = lca.getLCA(h[i], sta[top - 1]);
            if (l != sta[top - 1]) {
                while (dfsOrder[sta[top - 2]] > dfsOrder[l]) {
                    virtualTree[sta[top - 2]].push_back(sta[top - 1]);
                    top--;
                }
                if (l != sta[top - 2]) {
                    virtualTree[l].clear();
                    virtualTree[l].push_back(sta[top - 1]);
                    sta[top - 1] = l;
                } else {
                    virtualTree[sta[top - 2]].push_back(sta[top - 1]);
                    top--;
                }
            }
            virtualTree[h[i]].clear();
            sta[top++] = h[i];
        }
        while (--top >= 1) {
            virtualTree[sta[top - 1]].push_back(sta[top]);
        }
        dfs(1);
        cout << dp[1] << '\n';
    }
    return 0;
}
#include <format>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

tuple<int, int, vector<int>> dfs_D(const vector<vector<int>>& tree)
{
    vector<int>              d1(tree.size());
    int                      rt1  = 0;
    int                      rt2  = 0;
    function<void(int, int)> dfs1 = [&](int cur, int father) -> void {
        // d1[cur] = d1[father] + 1;
        if (d1[cur] > d1[rt1]) rt1 = cur;
        for (int adj : tree[cur]) {
            if (adj == father) continue;
            d1[adj] = d1[cur] + 1;
            dfs1(adj, cur);
        }
    };
    function<void(int, int)> dfs2 = [&](int cur, int father) -> void {
        // d1[cur] = d1[father] + 1;
        if (d1[cur] > d1[rt2]) rt2 = cur;
        for (int adj : tree[cur]) {
            if (adj == father) continue;
            d1[adj] = d1[cur] + 1;
            dfs2(adj, cur);
        }
    };
    dfs1(1, 0);
    d1.assign(d1.size(), 0);
    dfs2(rt1, 0);
    return {rt1, rt2, d1};
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
    int n;
    cin >> n;
    vector<vector<int>> tree(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
        degree[u]++;
        degree[v]++;
    }
    auto&& [rt1, rt2, distVec] = dfs_D(tree);
    vector<int>                   vec(tree.size());
    function<void(int, int, int)> dfs = [&](int u, int fa, int dis) -> void {
        if (dis > distVec[u]) {
            vec[u]     = rt2;
            distVec[u] = dis;
        } else {
            vec[u] = rt1;
        }
        for (int adj : tree[u]) {
            if (adj == fa) continue;
            dfs(adj, u, dis + 1);
        }
    };
    dfs(rt2, rt2, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 1 && i != rt1 && i != rt2) {
            q.push(i);
        }
    }
    vector<string> ans;
    i64            ansval = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        string temp = format("{} {} {}", cur, vec[cur], cur);
        ansval += distVec[cur];
        ans.push_back(temp);
        for (int i : tree[cur]) {
            degree[i]--;
            if (degree[i] == 1) {
                q.push(i);
            }
        }
    }
    q.push(rt1);
    ansval += (i64)(distVec[rt2] + 1) * distVec[rt2] / 2;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        string temp = format("{} {} {}", cur, rt2, cur);
        ans.push_back(temp);
        for (int i : tree[cur]) {
            degree[i]--;
            if (degree[i] == 1) {
                q.push(i);
            }
        }
    }
    cout << ansval << '\n';
    for (auto& i : ans) {
        cout << i << '\n';
    }
    return 0;
}
#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iostream>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using i64                  = long long;
using PII                  = pair<int, int>;
constexpr int          INF = 1e9;
vector<pair<int, int>> d1, d2;
vector<bool>           vis;

vector<int> dfs_D(const vector<vector<int>>& tree, int root)
{
    vector<int>              ans{1, root, root};
    function<void(int, int)> dfs = [&](int u, int fa) -> void {
        d1[u] = {u, 0}, d2[u] = {u, 0};
        for (int adj : tree[u]) {
            if (adj == fa || vis[adj]) continue;
            dfs(adj, u);
            int t = d1[adj].second + 1;
            if (t > d1[u].second || (t == d1[u].second && d1[adj].first > d1[u].first)) {
                d2[u] = d1[u], d1[u] = {d1[adj].first, t};
            } else if (t > d2[u].second || (t == d2[u].second && d1[adj].first > d2[u].first)) {
                d2[u] = {d1[adj].first, t};
            }
        }
        vector<int> temp{d1[u].second + d2[u].second + 1, max(d1[u].first, d2[u].first), min(d1[u].first, d2[u].first)};
        if (temp > ans) {
            ans = temp;
        }
    };
    dfs(root, 0);
    return ans;
}

// 

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    d1.resize(n + 1), d2.resize(n + 1);
    vis.assign(n + 1, false);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    deque<int> q;
    q.push_back(1);
    vector<int>                  father(n + 1);
    function<void(int u, int f)> mapFather = [&](int u, int f) {
        father[u] = f;
        for (int adj : graph[u]) {
            if (adj == f || vis[adj]) continue;
            mapFather(adj, u);
        }
    };
    vector<array<int, 3>> ans;
    while (!q.empty()) {
        int cur = q.back();
        q.pop_back();
        auto rtvec = dfs_D(graph, cur);
        mapFather(rtvec[2], 0);
        int u = rtvec[1];
        for (; u != 0; u = father[u]) {
            vis[u] = true;
            for (int adj : graph[u]) {
                if (adj != father[u] && !vis[adj]) {
                    q.push_back(adj);
                }
            }
        }
        ans.push_back({rtvec[0], rtvec[1], rtvec[2]});
    }
    sort(ans.begin(), ans.end(), [](const auto& a, const auto& b) {
        return a[0] > b[0] || (a[0] == b[0] && (a[1] > b[1] || (a[1] == b[1] && a[2] > b[2])));
    });
    for (auto i : ans) {
        cout << i[0] << ' ' << i[1] << ' ' << i[2] << ' ';
    }
    cout << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
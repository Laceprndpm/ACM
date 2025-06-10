#include <deque>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    vector<vector<int>>      color_root(n + 1);
    vector<vector<int>>      virtualTree(n + 1);
    vector<deque<int>>       color_stack(n + 1);
    vector<int>              timeIn(n + 1), timeOut(n + 1);
    vector<int>              siz(n + 1);
    int                      T    = 0;
    function<void(int, int)> init = [&](int v, int p) -> void {
        timeIn[v] = T++;
        // ord.push_back(v);
        siz[v] = 1;
        for (const auto& [u, w] : graph[v]) {
            if (u == p) continue;
            init(u, v);
            siz[v] += siz[u];  // 累加子树大小
        }
        timeOut[v] = T;  // 离开时间戳
    };
    init(1, 0);
    function<int(int, int)> isP = [&](int v, int u) -> int {
        return timeIn[v] <= timeIn[u] && timeOut[v] >= timeOut[u];
    };
    function<void(int, int)> add_edge = [&](int u, int v) {
        virtualTree[u].push_back(v);
    };
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (const auto& [v, w] : graph[u]) {
            if (v == fa) continue;
            while (!color_stack[w].empty() && !isP(color_stack[w].back(), v)) {
                int temp = color_stack[w].back();
                color_stack[w].pop_back();
                if (color_stack[w].empty()) {
                    color_root[w].push_back(temp);
                } else {
                    add_edge(color_stack[w].back(), temp);
                }
            }
            color_stack[w].push_back(v);
            dfs(v, u);
        }
    };
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        while (color_stack[i].size() >= 2) {
            int temp = color_stack[i].back();
            color_stack[i].pop_back();
            add_edge(color_stack[i].back(), temp);
        }
        if (!color_stack[i].empty()) {
            color_root[i].push_back(color_stack[i].back());
        }
    }
    i64                     ans    = 0;
    function<i64(int, int)> dfsAns = [&](int u, int fa) -> i64 {
        i64 curSiz = siz[u];
        for (auto adj : virtualTree[u]) {
            curSiz -= siz[adj];
        }
        for (auto adj : virtualTree[u]) {
            ans += dfsAns(adj, u) * curSiz;
        }
        return curSiz;
    };
    for (int i = 1; i <= n; i++) {
        virtualTree[1] = std::move(color_root[i]);
        dfsAns(1, 0);
    }
    cout << ans << '\n';
    return 0;
}

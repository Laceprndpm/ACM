#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

// 每条边只能经过一次
// 无环，所以每两个点之间路径唯一?
//
void solve()
{
    int n, st, en;
    cin >> n >> st >> en;
    Graph graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    vector<int>              ans;
    vector<int>              vis(n + 1);
    function<bool(int root)> DFS = [&](int root) {
        vis[root] = true;
        if (root == en) {
            ans.push_back(en);
            return true;
        }
        for (int adj : graph[root]) {
            if (!vis[adj]) {
                bool isFound = DFS(adj);
                if (isFound) {
                    ans.push_back(root);
                    return true;
                }
            }
        }
        return false;
    };
    DFS(st);
    vector<bool>             vis2(n + 1, false);
    function<void(int root)> DFS2 = [&](int root) {
        vis2[root] = true;
        for (int adj : graph[root]) {
            if (!vis2[adj]) {
                DFS2(adj);
            }
        }
        cout << root << ' ';
    };
    for (int i : ans) {
        vis2[i] = true;
    }
    // unordered_set<int> adjST(graph[st].begin(), graph[st].end());
    reverse(ans.begin(), ans.end());
    for (int i : ans) {
        DFS2(i);
    }
    cout << '\n';
    return;
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

// 1.将点分为路径点和非路径点
// 2.对于路径点，从远到近遍历完所有非路径点后，必然停留在某邻接点
// 3.给出那个路径点，这样    // for (int i = 1; i <= n; i++) {  // 出现在其他地方，且不相邻，不在路上
//     if (routePoint.count(i) == 0 && adjST.count(i) == 0) {
//         midans.emplace_back(i);
//     }
// }

// for (int i : adjST) {  // 出现在相邻地方，保证这些点间肯定不相邻，且不在路上
//     if (routePoint.count(i) == 0) {
//         lastans.emplace_back(i);
//     }
// }
// for (int i : midans) {  // 先浪费掉n
//     cout << i << ' ';
// }
// for (int i : lastans) {
//     cout << i << ' ';
// }
// for (int i : ans) {
//     cout << i << ' ';
// }
// cout << '\n';
// if (ans.size() == n) {
//     for (int i : ans) {
//         cout << i << ' ';
//     }
//     cout << '\n';
//     return;
// } else {
//     if (ans.size() == n - 1) {
//         for (int i = 1; i < n; i++) {
//             cout << ans[i] << ' ';
//         }
//         cout << '\n';
//         return;
//     }
// }
// #include <deque>
// #include <functional>
// #include <iostream>
// #include <vector>
// using namespace std;
// using i64         = long long;
// using PII         = pair<int, int>;
// constexpr int INF = 1e9;

// void solve()
// {
//     int n;
//     cin >> n;
//     vector<vector<int>> graph(n + 1);
//     vector<int>         deg(n + 1);
//     for (int i = 0; i < n - 1; i++) {
//         int u, v;
//         cin >> u >> v;
//         graph[u].push_back(v);
//         graph[v].push_back(u);
//         deg[u]++, deg[v]++;
//     }
//     vector<int> tag(n + 1, 2);
//     for (int i = 1; i <= n; i++) {
//         if (deg[i] == 1) {
//             tag[i]           = 0;
//             tag[graph[i][0]] = min(tag[graph[i][0]], 1);
//         }
//     }
//     // 即使赢不了，但想不输还是很简单的吗？
//     // 对，因为它必须移动
//     // 假如q周围全是树叶，p可以轻松移走
//     // 充分必要条件：以p为根，q的父亲存在树叶，且q不可为叶，且p节点无树叶，或q已经是叶子
//     //
//     int                 tot1 = std::count(tag.begin() + 1, tag.end(), 1);
//     int                 tot2 = std::count(tag.begin() + 1, tag.end(), 2);
//     int                 ans  = 0;
//     vector<int>         end_normal(n + 1);
//     vector<int>         end_fa_leaves(n + 1);
//     vector<int>         fa(n + 1);
//     function<void(int)> dfs = [&](int u) {
//         // bool son_can_win = false;
//         end_normal[u]    = (tag[u] == 2);
//         end_fa_leaves[u] = (tag[u] == 1);
//         for (int adj : graph[u]) {
//             if (adj == fa[u]) continue;
//             end_normal[u] += end_normal[adj];
//             end_fa_leaves[u] += end_fa_leaves[adj];
//             // if (deg[adj] == 1) {
//             //     son_can_win = 1;
//             // }
//             if (tag[u] == 0) {
//                 ans += end_fa_leaves[adj] + end_normal[adj];
//             } else if (tag[adj] == 1) {
//                 ans += end_normal[adj];
//             }
//             if (tag[adj] == 0) {
//                 ans += tot1 - end_fa_leaves[adj] + tot2 - end_normal[adj];
//             } else if (tag[u] == 1) {
//                 ans += tot2 - end_normal[adj];
//             }
//         }
//     };
//     dfs(1);
//     cout << ans << '\n';
//     // deque<int> leaves;
//     // for (int i = 1; i <= n; i++) {
//     //     if (deg[i] == 1) leaves.push_back(i);
//     // }
//     // vector<int> vis(n + 1);
//     // int         cnt = 0;
//     // deque<int>  check_list;
//     // for (int i : leaves) {
//     //     if (vis[graph[i][0]] != 1 && deg[graph[i][0]] != 1) {
//     //         vis[graph[i][0]] = 1;
//     //         check_list.push_back(i);
//     //     }
//     // }

//     // int cntLeaves = leaves.size();
//     // int ans1      = (cnt - cntLeaves) * (n - cnt - cntLeaves);
//     // int ans2      = cntLeaves * (n - cntLeaves);
//     // cout << ans1 + ans2 << '\n';
// }

// signed main(int argc, char** argv)
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
// #ifdef BATCH
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
//     // 明显的
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }

// // #include <algorithm>
// // #include <iostream>
// // #include <vector>
// // using i64  = long long;
// // using u64  = unsigned long long;
// // using u32  = unsigned;
// // using u128 = unsigned __int128;

// // void solve()
// // {
// //     int n;
// //     std::cin >> n;

// //     std::vector<std::vector<int>> adj(n);
// //     for (int i = 1; i < n; i++) {
// //         int u, v;
// //         std::cin >> u >> v;
// //         u--;
// //         v--;
// //         adj[u].push_back(v);
// //         adj[v].push_back(u);
// //     }

// //     std::vector<int> d(n, 2);
// //     for (int i = 0; i < n; i++) {
// //         if (adj[i].size() == 1) {
// //             d[i]  = 0;
// //             int x = adj[i][0];
// //             d[x]  = std::min(d[x], 1);
// //         }
// //     }

// //     int              tot1 = std::count(d.begin(), d.end(), 1);
// //     int              tot2 = std::count(d.begin(), d.end(), 2);
// //     std::vector<int> siz2(n), p(n, -1), siz1(n);

// //     i64  ans = 0;
// //     auto dfs = [&](this auto &&self, int x) -> void {
// //         siz2[x] = (d[x] == 2);
// //         siz1[x] = (d[x] == 1);
// //         for (auto y : adj[x]) {
// //             if (y == p[x]) {
// //                 continue;
// //             }
// //             p[y] = x;
// //             self(y);
// //             siz2[x] += siz2[y];
// //             siz1[x] += siz1[y];

// //             if (d[x] == 0) {
// //                 ans += siz1[y] + siz2[y];
// //             } else if (d[y] == 1) {
// //                 ans += siz2[y];
// //             }
// //             if (d[y] == 0) {
// //                 ans += tot1 - siz1[y] + tot2 - siz2[y];
// //             } else if (d[x] == 1) {
// //                 ans += tot2 - siz2[y];
// //             }
// //         }
// //     };
// //     dfs(0);

// //     std::cout << ans << "\n";
// // }

// // int main()
// // {
// //     std::ios::sync_with_stdio(false);
// //     std::cin.tie(nullptr);

// //     int t;
// //     std::cin >> t;

// //     while (t--) {
// //         solve();
// //     }

// //     return 0;
// // }
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
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
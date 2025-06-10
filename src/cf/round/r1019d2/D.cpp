// #include <algorithm>
// #include <deque>
// #include <functional>
// #include <iostream>
// #include <numeric>
// #include <vector>
// using namespace std;
// using i64         = long long;
// using PII         = pair<int, int>;
// constexpr int INF = 1e9;

// void solve()
// {
//     int n;
//     cin >> n;
//     vector<int> cmd(n + 1);
//     for (int i = 1; i <= n; i++) {
//         cin >> cmd[i];
//     }
//     int         up = *max_element(cmd.begin() + 1, cmd.end());
//     vector<int> lst(n + 2);
//     vector<int> nxt(n + 2);
//     iota(lst.begin(), lst.end(), -1);
//     iota(nxt.begin(), nxt.end(), 1);
//     lst[1] = 0;
//     nxt[n] = 0;
//     vector<vector<int>> greatArrow(n + 1);
//     vector<int>         degree(n + 1);
//     for (int i = 1; i <= up; i++) {
//         for (int j = 1; j <= n; j++) {
//             if (cmd[j] > i || cmd[j] == -1) {
//                 if (i % 2 == 1) {
//                     if (lst[j] != 0) {
//                         greatArrow[lst[j]].push_back(j);
//                         degree[j]++;
//                     }
//                     if (nxt[j] != 0) {
//                         greatArrow[nxt[j]].push_back(j);
//                         degree[j]++;
//                     }
//                 } else {
//                     if (lst[j] != 0) {
//                         greatArrow[j].push_back(lst[j]);
//                         degree[lst[j]]++;
//                     }
//                     if (nxt[j] != 0) {
//                         greatArrow[j].push_back(nxt[j]);
//                         degree[nxt[j]]++;
//                     }
//                 }
//             }
//         }
//         vector<bool> vis(n + 1);
//         if (cmd[1] == i) {
//             if (i % 2 == 1) {
//                 int j = 1;
//                 while (nxt[j] && cmd[nxt[j]] == i) {
//                     vis[j] = true;
//                     greatArrow[j].push_back(nxt[j]);
//                     degree[nxt[j]]++;
//                     j      = nxt[j];
//                     vis[j] = true;
//                 }
//             } else {
//                 int j = 1;
//                 while (nxt[j] && cmd[nxt[j]] == i) {
//                     vis[j] = true;
//                     greatArrow[nxt[j]].push_back(j);
//                     degree[j]++;
//                     j      = nxt[j];
//                     vis[j] = true;
//                 }
//             }
//         }
//         if (cmd[n] == i) {
//             if (i % 2 == 1) {
//                 int j = n;
//                 while (lst[j] && cmd[lst[j]] == i) {
//                     vis[j] = true;
//                     greatArrow[j].push_back(lst[j]);
//                     degree[lst[j]]++;
//                     j = lst[j];
//                     vis[j] = true;
//                 }
//             } else {
//                 int j = n;
//                 while (lst[j] && cmd[lst[j]] == i) {
//                     vis[j] = true;
//                     greatArrow[lst[j]].push_back(j);
//                     degree[j]++;
//                     j = lst[j];
//                     vis[j] = true;
//                 }
//             }
//         }
//         for (int j = 1; j <= n; j++) {
//             if (cmd[j] == i && !vis[j]) {
//                 while (nxt[j] && cmd[nxt[j]] == i) {
//                     vis[j] = true;
//                     greatArrow[j].push_back(nxt[j]);
//                     degree[nxt[j]]++;
//                     j = nxt[j];
//                 }
//             }
//         }
//         for (int j = 1; j <= n; j++) {
//             if (cmd[j] == i) {
//                 nxt[lst[j]] = nxt[j];
//                 lst[nxt[j]] = lst[j];
//             }
//         }
//     }
//     deque<int> que;
//     for (int i = 1; i <= n; i++) {
//         if (degree[i] == 0) {
//             que.push_back(i);
//         }
//     }
//     int         cur = n;
//     vector<int> ans(n + 1);
//     while (!que.empty()) {
//         int top = que.front();
//         que.pop_front();
//         ans[top] = cur--;
//         for (int adj : greatArrow[top]) {
//             degree[adj]--;
//             if (degree[adj] == 0) {
//                 que.push_back(adj);
//             }
//         }
//     }
//     // for (int i = 1; i <= n;) {
//     //     int j = i + 1;
//     //     while (cmd[i] == cmd[j]) {
//     //         j++;
//     //     }
//     //     if ((i == 1 && cmd[1] % 2 == 1) || (j == n + 1 && cmd[n] % 2 == 0)) {
//     //         sort(ans.begin() + i, ans.begin() + j, greater<int>());
//     //     } else {
//     //         sort(ans.begin() + i, ans.begin() + j, less<int>());
//     //     }
//     //     i = j;
//     // }
//     for (int i = 1; i <= n; i++) {
//         cout << ans[i] << ' ';
//     }
//     cout << '\n';
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
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }
#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
int           n;

void solve()
{
    cin >> n;
    vector<int> cmd(n + 1);
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cmd[i];
    }
    int l = 1, r = n;
    for (int depth = 1; depth <= 20; depth++) {
        int mr = n;
        while (mr >= 1 && cmd[mr] <= depth && cmd[mr] != -1) {
            mr--;
        }
        for (int j = 1; j <= mr; j++) {
            if (cmd[j] == depth) {
                ans[j] = ((depth % 2 == 1) ? r-- : l++);
            }
        }
        for (int j = n; j >= mr; j--) {
            if (cmd[j] == depth) {
                ans[j] = ((depth % 2 == 1) ? r-- : l++);
            }
        }
    }
    auto it               = find(cmd.begin() + 1, cmd.end(), -1);
    ans[it - cmd.begin()] = l;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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
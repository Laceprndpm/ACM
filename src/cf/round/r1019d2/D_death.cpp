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

void solve()
{
    int n;
    cin >> n;
    vector<int> cmd(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cmd[i];
    }
    int         up = *max_element(cmd.begin() + 1, cmd.end());
    vector<int> lst(n + 2);
    vector<int> nxt(n + 2);
    iota(lst.begin(), lst.end(), -1);
    iota(nxt.begin(), nxt.end(), 1);
    vector<vector<int>> greatArrow(n + 1);
    vector<int>         degree(n + 1);
    for (int i = 1; i <= up; i++) {
        for (int j = 1; j <= n; j++) {
            if (cmd[j] > i || cmd[j] == -1) {
                if (i % 2 == 1) {
                    if (lst[j] != 0) {
                        greatArrow[lst[j]].push_back(j);
                        degree[j]++;
                    }
                    if (nxt[j] != n + 1) {
                        greatArrow[nxt[j]].push_back(j);
                        degree[j]++;
                    }
                } else {
                    if (lst[j] != 0) {
                        greatArrow[j].push_back(lst[j]);
                        degree[lst[j]]++;
                    }
                    if (nxt[j] != n + 1) {
                        greatArrow[j].push_back(nxt[j]);
                        degree[nxt[j]]++;
                    }
                }
            }
        }
        // vector<bool> vis(n + 1);
        int mr = n;
        while (cmd[mr] <= i && cmd[mr] != -1) {
            mr--;
        }
        if (i % 2 == 1) {
            // int j = 0;
            // while (nxt[j] && cmd[nxt[j]] == i && nxt[j] <= mr) {
            //     // vis[j] = true;
            //     greatArrow[j].push_back(nxt[j]);
            //     degree[nxt[j]]++;
            //     j = nxt[j];
            //     // vis[j] = true;
            // }
            for (int j = 1; j <= mr; j++) {
                if (cmd[j] == i && cmd[nxt[j]] == i) {
                    greatArrow[j].push_back(nxt[j]);
                    degree[nxt[j]]++;
                }
            }
        } else {
            int j = 0;
            // while (nxt[j] && cmd[nxt[j]] == i && nxt[j] <= mr) {
            //     // vis[j] = true;
            //     greatArrow[nxt[j]].push_back(j);
            //     degree[j]++;
            //     j = nxt[j];
            //     // vis[j] = true;
            // }
            for (int j = 1; j <= mr; j++) {
                if (cmd[j] == i && cmd[nxt[j]] == i) {
                    greatArrow[nxt[j]].push_back(j);
                    degree[j]++;
                }
            }
        }
        if (i % 2 == 1) {
            // int j = n + 1;
            // while (lst[j] && cmd[lst[j]] == i && nxt[j] <= mr) {
            //     // vis[j] = true;
            //     greatArrow[j].push_back(lst[j]);
            //     degree[lst[j]]++;
            //     j = lst[j];
            //     // vis[j] = true;
            // }
            for (int j = n; j >= mr; j--) {
                if (cmd[j] == i && cmd[lst[j]] == i) {
                    greatArrow[j].push_back(lst[j]);
                    degree[lst[j]]++;
                }
            }
        } else {
            // int j = n + 1;
            // while (lst[j] && cmd[lst[j]] == i && nxt[j] <= mr) {
            //     // vis[j] = true;
            //     greatArrow[lst[j]].push_back(j);
            //     degree[j]++;
            //     j = lst[j];
            //     // vis[j] = true;
            // }
            for (int j = n; j >= mr; j--) {
                if (cmd[j] == i && cmd[lst[j]] == i) {
                    greatArrow[lst[j]].push_back(j);
                    degree[j]++;
                }
            }
        }
        // for (int j = 1; j <= n; j++) {
        //     if (cmd[j] == i && !vis[j]) {
        //         while (nxt[j] && cmd[nxt[j]] == i) {
        //             vis[j] = true;
        //             greatArrow[j].push_back(nxt[j]);
        //             degree[nxt[j]]++;
        //             j = nxt[j];
        //         }
        //     }
        // }
        for (int j = 1; j <= n; j++) {
            if (cmd[j] == i) {
                nxt[lst[j]] = nxt[j];
                lst[nxt[j]] = lst[j];
            }
        }
    }
    deque<int> que;
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            que.push_back(i);
        }
    }
    int         cur = n;
    vector<int> ans(n + 1);
    while (!que.empty()) {
        int top = que.front();
        que.pop_front();
        ans[top] = cur--;
        for (int adj : greatArrow[top]) {
            degree[adj]--;
            if (degree[adj] == 0) {
                que.push_back(adj);
            }
        }
    }
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
#include <bits/stdc++.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <ctime>
#include <deque>
#include <functional>
#include <limits>
#include <random>
#include <vector>
using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()
#define pb(x)  push_back(x)
constexpr i64 INF = 1e16;
mt19937       rd(time(0));

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> board(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> board[i][j];
            board[j][i] = board[i][j];
        }
    }
    vector<vector<int>> sons(n + 1);
    vector<int>         indeg(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int lac = board[i][j] ^ board[1][i] ^ board[1][j];
            if (lac == i) {
                indeg[j]++;
                sons[i].pb(j);
            } else if (lac == j) {
                indeg[i]++;
                sons[j].pb(i);
            } else {
                indeg[i]++;
                indeg[j]++;
                sons[lac].pb(i);
                sons[lac].pb(j);
            }
        }
    }
    deque<int> que;
    que.pb(1);
    vector<int> fa(n + 1);
    while (!que.empty()) {
        int u = que.front();
        que.pop_front();
        for (int v : sons[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                fa[v] = u;
                que.pb(v);
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        cout << fa[i] << ' ' << i << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
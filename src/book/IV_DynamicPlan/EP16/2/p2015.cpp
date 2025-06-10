#include <bits/stdc++.h>
using namespace std;
using i64                = long long;
using PII                = pair<int, int>;
constexpr int       INF  = 1e9;
constexpr int       MAXN = 110;
vector<vector<int>> dp;
// 节点root，保留x根树枝
int  leftNode[MAXN], rightNode[MAXN];
bool hasson[MAXN];
int  value[MAXN];

void DFS(int root, int x)  // 节点root，保留x根树枝
{
    int ans = 0;
    if (hasson[root]) {
        for (int i = 0; i <= x; i++) {
            int leftans  = 0;
            int rightans = 0;
            int leftn    = leftNode[root];
            int rightn   = rightNode[root];
            if (i != 0) {
                if (dp[leftn][i - 1] == -1) {
                    DFS(leftn, i - 1);
                }
                leftans += dp[leftn][i - 1] + value[leftn];
            }
            if (i != x) {
                if (dp[rightn][x - i - 1] == -1) {
                    DFS(rightn, x - i - 1);
                }
                rightans += dp[rightn][x - i - 1] + value[rightn];
            }
            ans = max(leftans + rightans, ans);
        }
    }
    dp[root][x] = ans;
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
    int n, q;
    cin >> n >> q;
    dp.resize(MAXN, vector<int>(MAXN, -1));
    vector<vector<pair<int, int>>> graph(n + 1);
    vector<int>                    degree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
        degree[u]++;
        degree[v]++;
    }
    function<void(int, int)> sortTree = [&](int x, int lst) {
        for (pair<int, int> i : graph[x]) {
            if (i.first != lst) {
                if (leftNode[x] == 0) {
                    leftNode[x] = i.first;
                } else {
                    rightNode[x] = i.first;
                }
                value[i.first] = i.second;
                hasson[x]      = true;
                sortTree(i.first, x);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (degree[i] == 2) {
            sortTree(i, 0);
            DFS(i, q);
            cout << dp[i][q];
            break;
        }
    }
    return 0;
}
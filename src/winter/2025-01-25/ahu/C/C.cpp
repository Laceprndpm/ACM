#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int                            dp[200][200][27];
vector<vector<pair<int, int>>> Graph(200);

int DFS(int i, int j, int k) {
    if (dp[i][j][k] != -1) {
        return dp[i][j][k];
    }

    for (auto iter : Graph[i]) {
        if (k > iter.second)
            continue;
        if (DFS(j, iter.first, iter.second) == 0) {
            dp[i][j][k] = 1;
            return 1;
        }
    }
    dp[i][j][k] = 0;
    return 0;
}

void solve(void) {
    int n, m;
    cin >> n >> m;
    int  u, v;
    char c;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> c;
        Graph[u].emplace_back(v, c - 'a' + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << (DFS(i, j, 0) == 1 ? 'A' : 'B');
        }
        cout << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    memset(dp, -1, sizeof(dp));
    solve();
    return 0;
}

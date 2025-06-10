#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<array<bool, 30>>> graphF(n, vector<array<bool, 30>>(n));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graphF[u][v][0] = 1;
    }
    for (int i = 1; i < 30; i++) {
        for (int j = 0; j < n; j++) {      // 起点
            for (int k = 0; k < n; k++) {  // 终点
                for (int middle = 0; middle < n; middle++) {
                    graphF[j][k][i] |= graphF[j][middle][i - 1] & graphF[middle][k][i - 1];
                }
            }
        }
    }
    vector<vector<int>> graphF_final(n, vector<int>(n));
    for (auto &i : graphF_final) {
        for (auto &j : i) {
            j = INF;
        }
    }
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < n; j++) {      // 起点
            for (int k = 0; k < n; k++) {  // 终点
                if (graphF[j][k][i]) {
                    graphF_final[j][k] = 1;
                }
            }
        }
    }
    for (int j = 0; j < n; j++) {      // 起点
        for (int k = 0; k < n; k++) {  // 终点
            for (int middle = 0; middle < n; middle++) {
                graphF_final[j][k] = min(graphF_final[j][middle] + graphF_final[middle][k], graphF_final[j][k]);
            }
        }
    }
    cout << graphF_final[0][n - 1];
    return 0;
}
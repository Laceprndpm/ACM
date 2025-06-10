#include <iostream>
#include <locale>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
bool          graph[20][20];

i64 lowbit(int x)
{
    return x & -x;
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
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u][v] = graph[v][u] = true;
    }
    i64                 nb = (1 << n) - 1;
    vector<vector<i64>> dp(nb + 1, vector<i64>(n));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 1;
    }
    i64 ans = 0;
    for (i64 s = 1; s <= nb; s++) {
        for (int i = 0; i < n; i++) {
            if (!(1 << i & s)) continue;
            for (int j = 0; j < n; j++) {
                if (graph[i][j]) {
                    if (lowbit(s) > 1 << j) continue;
                    if (lowbit(s) == 1 << j) {
                        ans += dp[s][i];
                    } else if (!(1 << j & s)) {
                        dp[1 << j | s][j] += dp[s][i];
                    }
                }
            }
        }
    }
    cout << (ans - m) / 2 << '\n';
    return 0;
}
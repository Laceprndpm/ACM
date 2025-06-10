#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int getNum1(int x)
{
    int cnt = 0;
    while (x) {
        if (x & 1) {
            cnt++;
        }
        x >>= 1;
    }
    return cnt;
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
    int n;
    cin >> n;
    vector<vector<int>> dist(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dist[i][j];
        }
    }
    int nB = (1 << n) - 1;

    vector<vector<int>> dp(n + 1, vector<int>(nB + 1, INF));
    dp[0][1] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= nB; j++) {  // start
            if (getNum1(j) != i) continue;
            for (int k = 0; k < n; k++) {  // to
                if ((~j) & (1 << k)) {
                    for (int s = 0; s < n; s++) {  // from
                        if (j & (1 << s)) {
                            dp[k][j | (1 << k)] = min(dp[k][j | (1 << k)], dp[s][j] + dist[s][k]);
                        }
                    }
                }
            }
        }
    }
    int ans = INF;
    for (int i = 1; i < n; i++) {
        ans = min(ans, dist[i][0] + dp[i][nB]);
    }
    cout << ans << '\n';
    return 0;
}
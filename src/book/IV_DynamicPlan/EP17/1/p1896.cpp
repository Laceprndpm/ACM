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

bool check(int x, int y)
{
    if (x & y) return false;
    if (x << 1 & y) return false;
    if (x >> 1 & y) return false;
    if (y >> 1 & y) return false;
    return true;
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
    int n, k;
    cin >> n >> k;
    int nb = (1 << n) - 1;

    vector<vector<vector<i64>>> dp(n + 1, vector<vector<i64>>(k + 1, vector<i64>(nb + 1)));
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {  // 上一层
            for (int lastb = 0; lastb <= nb; lastb++) {
                if (getNum1(lastb) > j) continue;
                if (lastb >> 1 & lastb) continue;
                for (int curb = 0; curb <= nb; curb++) {
                    if (check(lastb, curb)) {
                        int num1 = getNum1(curb);
                        if (num1 + j > k) continue;
                        dp[i][num1 + j][curb] += dp[i - 1][j][lastb];
                    }
                }
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i <= nb; i++) {
        ans += dp[n][k][i];
    }
    cout << ans << '\n';
    return 0;
}
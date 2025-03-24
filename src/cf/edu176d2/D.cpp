#include <cstdint>
#include <cstring>
#include <iostream>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           dp[70][70][70];

int gethigh(i64 x)
{
    int cnt = 0;
    while (x) {
        cnt++;
        x >>= 1;
    }
    return cnt;
}

void solve()
{
    i64 x, y;
    cin >> x >> y;

    int x1 = gethigh(x), y1 = gethigh(y);  // 最高位为x1-(1-indx)
    int x2 = x1, y2 = y1;
    while (x1 >= 1 && y1 >= 1 && (x >> (x1 - 1) & 1) == (y >> (y1 - 1) & 1)) {  // x1位等于y1位
        x1--;
        y1--;
    }
    i64 ans = INT32_MAX;
    for (int j = 0; j <= min(60 - x1, 60 - y1); j++) {
        ans = min(dp[60][x1 + j][y1 + j], ans);
    }
    for (int i = x2; i <= 60; i++) {
        for (int j = y2; j <= 60; j++) {
            ans = min(dp[60][i][j], ans);
        }
    }
    cout << ans << '\n';
}

// 110
// 10
// 因为整除是保留前位，一定是从前往后考虑
// 第一个失配位置直接除吗？似乎是的吧。。。
// 1000
// 1111
// 如果等位呢？
// 13 : 1101 3次方
// 37 : 100101 5次方，5=1+4
// 也就是说，第一失配位的前提下，使得k尽可能拆分，怎么样的拆分是更优的？
// dp如何？
// dp[i][x][y]
// dp[i+1][x][y] = dp[i][x-i-1][y]

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
    for (int i = 0; i < 70; i++) {
        for (int x = 0; x < 70; x++) {
            for (int y = 0; y < 70; y++) {
                dp[i][x][y] = INT64_MAX;
            }
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= 60; i++) {
        for (int x = 0; x <= 60; x++) {
            for (int y = 0; y <= 60; y++) {
                if (dp[i - 1][x][y] != INT64_MAX) dp[i][x][y] = min(dp[i - 1][x][y], dp[i][x][y]);  // 直接继承
                if (x >= i && dp[i - 1][x - i][y] != INT64_MAX)
                    dp[i][x][y] = min(dp[i - 1][x - i][y] + (1ll << i), dp[i][x][y]);  // 使用这一位
                if (y >= i && dp[i - 1][x][y - i] != INT64_MAX)
                    dp[i][x][y] = min(dp[i - 1][x][y - i] + (1ll << i), dp[i][x][y]);
            }
        }
    }
    while (t--) {
        solve();
    }
    return 0;
}
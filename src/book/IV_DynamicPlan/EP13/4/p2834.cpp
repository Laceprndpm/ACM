#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
constexpr int MOD = 1e9 + 7;
int           dp[(int)1e4 + 50];

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, w;
    cin >> n >> w;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        for (int j = cur; j <= w; j++) {
            dp[j] += dp[j - cur];
            dp[j] %= MOD;
        }
    }
    cout << dp[w];
    return 0;
}
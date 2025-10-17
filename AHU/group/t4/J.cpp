
#include <bits/stdc++.h>

#include <vector>
using i64 = long long;
using namespace std;
constexpr int INF = 1e9;

int main()
{
    int n, w;
    cin >> n >> w;
    vector<int> cnt(14);
    for (int i = 0, ai; i < n; i++) {
        cin >> ai;
        ai--;
        cnt[ai]++;
    }
    int         B = (1 << 13) - 1;
    vector<int> dp(B + 1, INF);
    dp[B] = 0;
    for (int cur = B; cur > 0; cur--) {
        for (int sons = cur; sons != -1; sons--) {
            sons &= cur;
            int choose = cur ^ sons;
            i64 cost   = 0;
            for (int j = 0; j < 13; j++) {
                if (choose >> j & 1) {
                    cost += cnt[j];
                }
            }
            if (cost <= w) {
                dp[sons] = min(dp[sons], dp[cur] + 1);
            }
        }
    }
    cout << dp[0] << '\n';
}
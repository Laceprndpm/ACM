#include <bits/stdc++.h>

using namespace std;

const int val[] = {1, 10, 100, 1000, 10000};
const int INF   = 1e9;

string s;
int    dp[2][5][2];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        reverse(s.begin(), s.end());
        for (int j = 0; j < 5; ++j)
            dp[0][j][0] = dp[0][j][1] = -INF;
        dp[0][0][0] = 0;
        for (auto c : s) {
            int cur = c - 'A';
            for (int j = 0; j < 5; ++j)
                dp[1][j][0] = dp[1][j][1] = -INF;
            for (int j = 0; j < 5; ++j) {
                for (int t = 0; t < 2; ++t) {
                    for (int y = 0; y < 5; ++y) {
                        int nj = max(j, y);
                        int nt = t + (cur != y);
                        if (nt < 2) dp[1][nj][nt] = max(dp[1][nj][nt], dp[0][j][t] + (y < nj ? -val[y] : val[y]));
                    }
                }
            }
            swap(dp[0], dp[1]);
        }
        int ans = -INF;
        for (int j = 0; j < 5; ++j)
            ans = max(ans, max(dp[0][j][0], dp[0][j][1]));
        cout << ans << '\n';
    }
}
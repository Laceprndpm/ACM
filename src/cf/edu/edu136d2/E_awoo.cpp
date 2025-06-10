#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < int(n); i++)

const int INF = 1e9;

int main()
{
    int n;
    cin >> n;
    vector<string> s(2);
    forn(i, 2) cin >> s[i];
    vector<array<array<int, 2>, 2>> dp(n + 1);
    forn(i, n + 1) forn(j, 2) forn(k, 2) dp[i][j][k] = -INF;
    dp[0][0][s[1][0] == '1']                         = s[1][0] == '1';
    dp[0][0][0]                                      = 0;
    forn(i, n - 1) forn(j, 2)
    {
        int nxtj            = s[j][i + 1] == '1';
        int nxtj1           = s[j ^ 1][i + 1] == '1';
        dp[i + 1][j ^ 1][0] = max(dp[i + 1][j ^ 1][0], dp[i][j][1] + nxtj1);
        dp[i + 1][j][nxtj1] = max(dp[i + 1][j][nxtj1], dp[i][j][0] + nxtj1 + nxtj);
        dp[i + 1][j][0]     = max(dp[i + 1][j][0], dp[i][j][0] + nxtj);
    }
    cout << max({dp[n - 1][0][0], dp[n - 1][0][1], dp[n - 1][1][0], dp[n - 1][1][1]}) << '\n';
}
#include <bits/stdc++.h>
using namespace std;
const long long mod = 998244353;
int             l[60];
int             vis[60][61][2];
long long       dp[61][61][2][2];

long long dfs(int p, int k, int lim)
{
    if (p == 60) {
        dp[p][k][lim][1] = 0;
        if (k)
            dp[p][k][lim][0] = 0;
        else
            dp[p][k][lim][0] = 1;
        return 0;
    }
    if (vis[p][k][lim]) return dp[p][k][lim][1];
    vis[p][k][lim] = 1;
    int i, tlim, tk;
    for (i = 0; i < 2; i++) {
        if (lim && i > l[p]) break;
        if (lim && i == l[p])
            tlim = 1;
        else
            tlim = 0;
        if (i)
            tk = k - 1;
        else
            tk = k;
        if (tk < 0) continue;
        dfs(p + 1, tk, tlim);
        dp[p][k][lim][0] = (dp[p][k][lim][0] + dp[p + 1][tk][tlim][0]) % mod;
        dp[p][k][lim][1] = (dp[p][k][lim][1] + dp[p + 1][tk][tlim][1]) % mod;
        if (i) dp[p][k][lim][1] = (dp[p][k][lim][1] + dp[p + 1][tk][tlim][0] * ((1LL << (59 - p)) % mod)) % mod;
    }
    return dp[p][k][lim][1];
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T;
    long long n, k, i, j;
    for (cin >> T; T > 0; T--) {
        cin >> n >> k;
        for (i = 0; i < 60; i++)
            l[i] = n >> (59 - i) & 1;
        for (i = 0; i < 60; i++) {
            for (j = 0; j <= 60; j++) {
                vis[i][j][0]   = 0;
                dp[i][j][0][0] = 0;
                dp[i][j][0][1] = 0;
                vis[i][j][1]   = 0;
                dp[i][j][1][0] = 0;
                dp[i][j][1][1] = 0;
            }
        }
        cout << dfs(0, k, 1) << '\n';
    }
    return 0;
}
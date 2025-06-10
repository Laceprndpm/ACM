#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e3 + 2;
bool board[N][N];

struct Range
{
    int lower;
    int upper;
    void forward(bool x, const Range &left, const Range &up)
    {
        lower = min(up.lower, left.lower);
        upper = max(up.upper, left.upper);
        if (x)
        {
            lower++;
            upper++;
        }
        else
        {
            lower--;
            upper--;
        }
    }
    Range(int lower = INT32_MAX, int upper = INT32_MIN) : lower(lower), upper(upper) {}
} dp[N][N];
bool init()
{
    char c = getchar();
    int x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return (x * f) == 1;
}

void solve(void)
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            board[i][j] = init();
        }
    }

    if ((m + n) % 2 == 0)
    {
        cout << "NO" << '\n';
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j].forward(board[i][j], dp[i][j - 1], dp[i - 1][j]);
        }
    }
    if (dp[n][m].lower <= 0 && dp[n][m].upper >= 0)
    {
        cout << "YES" << '\n';
    }
    else
    {
        cout << "NO" << '\n';
    }
}
signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    int t;
    cin >> t;
    dp[0][1] = Range(0, 0);
    while (t--)
    {
        solve();
    }

    return 0;
}
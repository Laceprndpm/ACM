#include <bits/stdc++.h>
#define int     long long
#define in      inline
#define ri      register
#define _123hh2 0
using namespace std;

in int read()
{
    int  x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x  = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

in void write(int x)
{
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

map<int, double> dp;
int              n, a, x, y;

double dfs(int now)
{
    if (now == 0) return 0;
    if (dp[now] != 0) return dp[now];
    double ans1 = 1.2 * y, ans2 = dfs(now / a) + x;
    double sum = 0;
    for (int i = 2; i <= 6; i++) {
        sum += dfs(now / i);
    }
    ans1 += sum / 5.0;
    return dp[now] = min(ans1, ans2);
}

signed main()
{
    n = read(), a = read(), x = read(), y = read();
    cout << fixed << setprecision(12) << dfs(n);
    return _123hh2;
}
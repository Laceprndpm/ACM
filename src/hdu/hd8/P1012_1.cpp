#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long    LL;
typedef pair<LL, LL> pr;
typedef vector<LL>   vi;

inline LL rd()
{
    LL   x = 0, y = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') y = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * y;
}

const LL p = 998244353, N = 3005;

LL n, m, f[N][N], T, a[N], rangeMin[N][N];

int main()
{
    for (T = rd(); T--;) {
        n = rd();
        for (LL i = 1; i <= n; ++i)
            a[i] = rd();
        for (LL i = 1; i <= n; ++i) {
            rangeMin[i][i] = a[i];
            for (LL j = i + 1; j <= n; ++j)
                rangeMin[i][j] = min(rangeMin[i][j - 1], a[j]);
        }
        memset(f, 0, sizeof(f));
        for (LL i = 0; i <= n; ++i)
            f[0][i] = 1;
        for (LL i = 1; i <= n; ++i) {
            for (LL j = 1; j <= n; ++j) {
                f[i][j] = f[i][j - 1];
                if (rangeMin[min(i, j)][max(i, j)] == a[j]) {
                    f[i][j] = (f[i][j] + f[i - 1][j]) % p;
                }
            }
        }
        printf("%lld\n", f[n][n]);
    }
    return 0;
}
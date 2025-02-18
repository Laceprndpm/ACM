#include <cstdio>

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

const int N = (int)1e6 + 5;
int       a[N], b[N], c[N], d[N], mu[N];
bool      vis[N];

signed main(signed argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n = init(), m = init();
    for (int i = 1; i <= n; ++i)
        a[init()]++;
    for (int j = 1; j <= m; ++j)
        b[init() - 1]++;

    for (int div = 1; div <= (int)1e6; ++div)
        for (int k = 1; k * div <= (int)1e6; ++k)
            c[div] += a[k * div], d[div] += b[k * div];
    
    for (int j = 1; j < N; ++j)
        mu[j] = 1;
    for (int i = 2; i < N; ++i)
        if (!vis[i]) {
            mu[i] = -1;
            for (int j = i << 1; j < N; j += i) {
                vis[j] = true;
                if (j % (i * i) == 0)
                    mu[j] = 0;
                else
                    mu[j] *= -1;
            }
        }
    // 边筛素数边预处理 mu[]
    long long ans = 0;
    for (int i = 1; i <= (int)1e6; ++i)
        ans += mu[i] * c[i] * 1ll * d[i];
    printf("%lld\n", ans);
}
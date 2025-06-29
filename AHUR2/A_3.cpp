#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int         MAXN   = 1e6;
const int         MAXLEN = 100;
const int         MOD    = 998244353;
const int         PHI    = MOD - 1;
const int         PPHI   = 402653184;

int getmod(ll x)
{
    return (x > PPHI) ? (x % PPHI + PPHI) : x;
}

int  pr[MAXN + 5], prcnt = 0, mu[MAXN + 5], prd[MAXN + 5];
bool vis[MAXN + 5];

int qpow(int x, int e)
{
    if (e < 0) e += PHI;
    int ret = 1;
    for (; e; e >>= 1, x = 1ll * x * x % MOD)
        if (e & 1) ret = 1ll * ret * x % MOD;
    return ret;
}

int _qpow(int x, int e)
{
    int ret = 1;
    for (; e; e >>= 1, x = 1ll * x * x % PHI)
        if (e & 1) ret = 1ll * ret * x % PHI;
    return ret;
}

void sieve(int n)
{
    mu[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) mu[i] = -1, pr[++prcnt] = i;
        for (int j = 1; j <= prcnt && pr[j] * i <= n; j++) {
            vis[pr[j] * i] = 1;
            if (i % pr[j] == 0) break;
            mu[pr[j] * i] = -mu[i];
        }
    }
    
    for (int i = 1; i <= n; i++)
        prd[i] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j * i <= n; j++)
            prd[i * j] = 1ll * prd[i * j] * qpow(i, mu[j]) % MOD;
    //    for(int i=1;i<=n;i++) printf("%d\n",prd[i]);
    prd[0] = 1;
    for (int i = 1; i <= n; i++)
        prd[i] = 1ll * prd[i - 1] * prd[i] % MOD;
}

int  n;
ll   k;
char buf[MAXLEN + 5];

void solve()
{
    scanf("%d%s", &n, buf + 1);
    k       = 0;
    int len = strlen(buf + 1);
    for (int i = 1; i <= len; i++)
        k = getmod(10ll * k + buf[i] - '0');
    int res = 1;
    for (int l = 1, r; l <= n; l = r + 1) {
        r   = (n / (n / l));
        res = 1ll * res
              * qpow(1ll * prd[r] * qpow(prd[l - 1], MOD - 2) % MOD, (_qpow(-n / l + n, k) - _qpow(n, k) + PHI) % PHI)
              % MOD;
    }
    printf("%d\n", qpow(res, MOD - 2));
}

int main()
{
    int qu;
    scanf("%d", &qu);
    sieve(MAXN);
    while (qu--)
        solve();
    return 0;
}
#include <bits/stdc++.h>

using namespace std;

#define ll long long

int qpow(int a, int b, int mod)
{  // 快速幂
    int ans = 1, t = a;
    for (; b > 0; b >>= 1) {
        if (b & 1) ans = ((ll)ans * t) % mod;
        t = ((ll)t * t) % mod;
    }
    return ans;
}

const int N = 10000050;

int  t, r, n, m, u, k;
int  phia[N], phib[N];  // phia(i)的a和b
int  tmsa[N], tmsb[N];  // i!的a和b
bool vis[N];

int main()
{
    cin >> t >> r;
    vis[1] = 1;
    // 埃氏筛筛质数
    for (int i = 1; i < N; i++)
        if (!vis[i])
            for (int j = i; (ll)j * i < N; j++) vis[i * j] = 1;
    // 预处理
    phia[0] = 1;
    phib[0] = 0;
    tmsa[0] = 1;
    tmsb[0] = 0;
    for (int i = 1; i < N; i++) {
        // 处理阶乘
        u = i, k = 0;
        while (u % r == 0) u /= r, k++;      // 将i中所有的r除出来
        tmsa[i] = ((ll)tmsa[i - 1] * u) % r; /*将a相乘*/
        tmsb[i] = tmsb[i - 1] + k /*将b相加*/;
        // 处理phi前缀积
        u = (vis[i] ? i : i - 1), k = 0;
        while (u % r == 0) u /= r, k++;      // 将i中所有的r除出来
        phia[i] = ((ll)phia[i - 1] * u) % r; /*将a相乘*/
        phib[i] = phib[i - 1] + k /*将b相加*/;
    }
    while (t--) {
        scanf("%d%d", &n, &m);
        int ans = (ll)tmsa[n] * phia[m] % r * qpow(tmsa[m], r - 2, r) % r;  // 求出答案的a
        if (tmsb[n] + phib[m] - tmsb[m] == 0)
            printf("%d\n", ans);  // 若答案的b为零，输出ans的a
        else
            printf("0\n");  // 否则答案为r的倍数，输出0
    }
    return 0;
}

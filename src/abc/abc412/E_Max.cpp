/**
 *@author MaxBlazeResFire
 */

#include <bits/stdc++.h>
using namespace std;

#define int  long long
#define MAXN 10000005
#define INF  0x3f3f3f3f

bool notPrime[MAXN] = {0}, vis[MAXN] = {0};
int  prime[MAXN], tot                = 0, L, R;

unordered_set<int> S;

inline bool isPrime(int x)
{
    for (int j = 1; j <= tot; j++)
        if (x % prime[j] == 0) return 0;
    return 1;
}

void solve()
{
    scanf("%lld%lld", &L, &R);
    int Ans = 0, flag = 0;
    for (int j = 1; j <= tot; j++) {
        int po = prime[j], pp = prime[j];
        while (po < L)
            po = po * prime[j];
        if (po == L) flag = 1;
        while (po <= R)
            Ans++, po = po * prime[j];
        for (int ST = L + (L % pp ? pp - L % pp : 0); ST <= R; ST += pp)
            vis[ST - L + 1] = 1;
    }
    if (!flag) Ans++;
    for (int i = 2; i <= R - L + 1; i++)
        if (!vis[i]) Ans++;
    printf("%lld\n", Ans);
    return;
    // 遍历所有质数prime[j]
    // 1. 统计区间内所有prime[j]的幂次（质数幂）
    // 2. 标记区间内所有能被prime[j]整除的合数（vis数组）

    // flag标记L是否为质数幂，若不是，则额外加1（具体含义需题意确认）

    // 遍历vis数组，统计未被标记的数（质数和可能的1）

    // 输出统计结果
}

inline void Euler()
{
    notPrime[1] = 1;
    for (int i = 2; i <= MAXN - 5; i++) {
        if (!notPrime[i]) prime[++tot] = i;
        for (int j = 1; j <= tot && i * prime[j] <= MAXN - 5; j++) {
            notPrime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

signed main()
{
    Euler();
    int testcase = 1;
    while (testcase--)
        solve();
    return 0;
}
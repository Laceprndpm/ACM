#include <bits/stdc++.h>
using namespace std;
const int MOD = 10000;
int qpow(int n, int p, int mod = MOD)
{
    int result = 1;
    while (p > 0)
    {
        if (p & 1)
        {
            result = (result * n) % mod;
        }
        n = (n * n) % mod;
        p >>= 1;
    }
    return result;
}

int x, C, k;
signed main()
{
    cin >> x >> C >> k;
    while (--k)
    {
        x = (qpow(x, 2) + C) % MOD;
    }
    cout << x;
}

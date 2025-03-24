#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
LL MOD;

LL qpow(LL n, LL q, LL mod = MOD)
{
    if (q == 0) {
        return 1;
    }
    LL ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int a, b, q;
    cin >> a >> b >> q;
    LL ans = qpow(a, b, q);
    printf("%d^%d mod %d=%lld", a, b, q, ans);
    return 0;
}
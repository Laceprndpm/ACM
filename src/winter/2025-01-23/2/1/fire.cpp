#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr LL MOD      = 998244353;
constexpr LL two_neg1 = 499122177;
constexpr LL N        = 1e9 + 5;

LL qpow(LL n, LL q, LL mod = MOD) {
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

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    LL n, k;
    cin >> n >> k;
    const LL two_negk = qpow(two_neg1, k);
    LL       p        = ((1 - two_negk) + MOD) % MOD;
    LL       p_neg    = qpow(p, MOD - 2);
    LL       temp     = (two_negk * (1 - qpow(two_negk, n) + MOD) % MOD) * p_neg % MOD;
    LL       x        = (two_negk * p_neg % MOD) * (MOD + n - temp) % MOD;
    LL       ans      = x * p % MOD;
    cout << ans;
    return 0;
}

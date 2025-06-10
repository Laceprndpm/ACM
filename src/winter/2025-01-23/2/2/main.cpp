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
    LL       x = 0, p = (1 - two_negk) + MOD;
    for (int i = 1; i <= n; i++) {
        x += qpow(two_negk, i);
        x %= MOD;
        k += p * x;
        k %= MOD;
    }
    cout << (k + MOD) % MOD << '\n';
    return 0;
}
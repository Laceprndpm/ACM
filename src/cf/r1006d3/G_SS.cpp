#include <bits/stdc++.h>
using namespace std;
const long long   mod = 1000000007;
vector<long long> v;

/**
 * Converts a number n to base p, calculates a specific sum modulo mod.
 * 
 * @param n The number to be converted.
 * @param p The base to convert to.
 * @return The calculated sum modulo mod.
 */
long long check(long long n, long long p)
{
    long long i, s = 0;
    while (n > 0) {
        v.push_back(n % p);
        n /= p;
    }
    for (i = 0; i < v.size(); i++)
        s = (s * p + v[i]) % mod;
    v.clear();
    return s;
}

/**
 * Calculates the sum of the first x natural numbers modulo mod.
 * 
 * @param x The upper limit of the sum.
 * @return The sum of the first x natural numbers modulo mod.
 */
long long F(long long x)
{
    x %= mod;
    return x * (x + 1) / 2 % mod;
}

/**
 * Calculates the sum of the squares of the first x natural numbers modulo mod.
 * 
 * @param x The upper limit of the sum of squares.
 * @return The sum of the squares of the first x natural numbers modulo mod.
 */
long long G(long long x)
{
    x %= mod;
    return x * (x + 1) * (x * 2 + 1) / 6 % mod;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T;
    long long n, k, i, cl, cr, w, ccr, ans;
    for (cin >> T; T > 0; T--) {
        cin >> n >> k;
        ans = 0;
        // Iterate over all possible divisors up to sqrt(n)
        for (i = 2; i * i <= n; i++) {
            if (i <= k) ans = (ans + check(n, i)) % mod;
        }
        // Handle the remaining divisors
        for (; i <= n; i++) {
            cl  = i;
            w   = n / i;
            cr  = n / w;
            ccr = min(cr, k);
            if (ccr >= cl)
                ans = (ans + w * (ccr - cl + 1) % mod + n * (F(ccr) + mod - F(cl - 1)) % mod
                       + (mod - w) * (G(ccr) + mod - G(cl - 1)) % mod)
                      % mod;
            i = cr;
        }
        // Handle the case when i <= k
        if (i <= k) ans = (ans + n * ((k - i + 1) % mod)) % mod;
        cout << ans << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
const long long mod        = 998244353;
long long       f[1 << 21] = {}, g[1 << 21] = {}, fntt[1 << 21], gntt[1 << 21], prodntt[1 << 21], prod[1 << 21], wi[22],
                 winv[22], trans[1 << 21]   = {}, inv;

long long qpow(long long a, long long b)
{
    long long ans = 1;
    while (b > 0) {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

void ntt(int t)
{
    int       i, j, k;
    long long x, u, v;
    for (i = 0; i < (1 << t); i++) {
        fntt[i] = f[trans[i]];
        gntt[i] = g[trans[i]];
    }
    for (i = 0; i < t; i++) {
        for (j = 0; j < (1 << t); j += (1 << (i + 1))) {
            x = 1;
            for (k = 0; k < (1 << i); k++) {
                u = fntt[j + k];
                v = fntt[j + k + (1 << i)] * x % mod;
                x *= wi[t - i - 1];
                x %= mod;
                fntt[j + k]            = (u + v) % mod;
                fntt[j + k + (1 << i)] = (u - v + mod) % mod;
            }
        }
        for (j = 0; j < (1 << t); j += (1 << (i + 1))) {
            x = 1;
            for (k = 0; k < (1 << i); k++) {
                u = gntt[j + k];
                v = gntt[j + k + (1 << i)] * x % mod;
                x *= wi[t - i - 1];
                x %= mod;
                gntt[j + k]            = (u + v) % mod;
                gntt[j + k + (1 << i)] = (u - v + mod) % mod;
            }
        }
    }
    for (i = 0; i < (1 << t); i++)
        prodntt[i] = fntt[i] * gntt[i] % mod;
    for (i = 0; i < (1 << t); i++)
        prod[i] = prodntt[trans[i]] * inv % mod;
    for (i = 0; i < t; i++) {
        for (j = 0; j < (1 << t); j += (1 << (i + 1))) {
            x = 1;
            for (k = 0; k < (1 << i); k++) {
                u = prod[j + k];
                v = prod[j + k + (1 << i)] * x % mod;
                x *= winv[t - i - 1];
                x %= mod;
                prod[j + k]            = (u + v) % mod;
                prod[j + k + (1 << i)] = (u - v + mod) % mod;
            }
        }
    }
}

int precalc(int n, int m)
{
    int       i, j, t, mem;
    long long w;
    for (t = 0; (1 << t) < n + m - 1; t++)
        ;
    inv = qpow((1 << t), mod - 2);
    for (i = 0; i < (1 << t); i++) {
        f[i]       = 0;
        g[i]       = 0;
        fntt[i]    = 0;
        gntt[i]    = 0;
        prod[i]    = 0;
        prodntt[i] = 0;
        trans[i]   = 0;
    }
    for (i = 0; i < (1 << t); i++) {
        mem = i;
        for (j = 0; j < t; j++) {
            if (mem >= (1 << (t - j - 1))) {
                trans[i] += (1 << j);
                mem -= (1 << (t - j - 1));
            }
        }
    }
    w       = qpow(3, (mod - 1) / (1 << t));
    wi[0]   = w;
    winv[0] = qpow(w, mod - 2);
    for (i = 1; i < t; i++) {
        wi[i]   = wi[i - 1] * wi[i - 1] % mod;
        winv[i] = winv[i - 1] * winv[i - 1] % mod;
    }
    return t;
}

long long tt[200001], intt[200001];

long long C(long long n, long long m)
{
    if (n < 0 || m < 0 || m > n) return 0;
    return tt[n] * intt[m] % mod * intt[n - m] % mod;
}

string s;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int       T;
    long long n, q, t, i, c, p;
    tt[0]   = 1;
    intt[0] = 1;
    tt[1]   = 1;
    intt[1] = 1;
    for (i = 2; i <= 200000; i++) {
        tt[i]   = i;
        intt[i] = (mod - mod / i) * intt[mod % i] % mod;
    }
    for (i = 2; i <= 200000; i++) {
        tt[i]   = tt[i - 1] * tt[i] % mod;
        intt[i] = intt[i - 1] * intt[i] % mod;
    }
    for (cin >> T; T > 0; T--) {
        cin >> n >> q >> s;
        t = precalc(n * 2 + 1, n + 1);
        for (i = 0; i <= n * 2; i++) {
            if (i <= n)
                c = n - i;
            else
                c = i - n;
            f[i] = (c / 2) * ((c + 1) / 2) % mod;
        }
        for (i = 0; i <= n; i++)
            g[i] = C(n, i);
        ntt(t);
        c = 0;
        for (i = 0; i < n; i++) {
            if (s[i] == '0') c++;
        }
        for (; q > 0; q--) {
            cin >> p;
            p--;
            if (s[p] == '0') {
                s[p] = '1';
                c--;
            } else {
                s[p] = '0';
                c++;
            }
            cout << prod[c + n] << '\n';
        }
    }
    return 0;
}
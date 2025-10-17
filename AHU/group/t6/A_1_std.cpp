#include <bits/stdc++.h>
#define up(a, b, c) for (int a = b; a <= c; ++a)
#define dn(a, b, c) for (int a = b; a >= c; --a)
constexpr int N = 2200, q[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}, p = 998244353;
using namespace std;
int n, a[N], b[N], c[N], f[1 << 15], g[1 << 15], as;

int ni(int n) { return n - 1 ? p - 1ll * p / n * ni(p % n) % p : 1; }

int main()
{
    cin >> n;
    up(i, 1, n)
    {
        cin >> a[i], b[i] = a[i];
        up(j, 0, 14) while (b[i] % q[j] == 0) b[i] /= q[j], c[i] |= 1 << j;
        if (b[i] % 53 == 0) b[i] = 53;
    }
    up(i, 1, n) up(j, i + 1, n) if (b[i] > b[j]) swap(a[i], a[j]), swap(b[i], b[j]), swap(c[i], c[j]);
    f[0] = 1;
    up(i, 1, n)
    {
        int e                       = ni(b[i]);
        dn(S, 32767, 0) g[S | c[i]] = (g[S | c[i]] + 1ll * (f[S] + g[S]) * a[i]) % p;
        if (b[i] != b[i + 1])
            up(S, 0, 32767) f[S] = (f[S] + (b[i] - 1 ? (b[i] - 1ll) * e % p : 1) * g[S]) % p, g[S] = 0;
    }
    up(S, 0, 32767)
    {
        up(i, 0, 14) if (S >> i & 1) f[S] = f[S] * (q[i] - 1ll) % p * ni(q[i]) % p;
        as                                = (as + f[S]) % p;
    }
    cout << as;
    return 0;
}

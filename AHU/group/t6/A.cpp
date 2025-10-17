#include <bits/stdc++.h>
const int N = 2200, q[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}, p = 998244353;
using namespace std;
int n, a[N], b[N], c[N], f[1 << 16], g[1 << 16], as;

int ni(int n) { return n - 1 ? p - 1ll * p / n * ni(p % n) % p : 1; }

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i], b[i] = a[i];
        for (int j = 0; j <= 15; ++j)
            while (b[i] % q[j] == 0) b[i] /= q[j], c[i] |= 1 << j;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (b[i] > b[j]) swap(a[i], a[j]), swap(b[i], b[j]), swap(c[i], c[j]);
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        int e = ni(b[i]);
        for (int S = 65535; S >= 0; --S) g[S | c[i]] = (g[S | c[i]] + 1ll * (f[S] + g[S]) * a[i]) % p;
        if (b[i] != b[i + 1])
            for (int S = 0; S <= 65535; ++S) f[S] = (f[S] + (b[i] - 1 ? (b[i] - 1ll) * e % p : 1) * g[S]) % p, g[S] = 0;
    }
    for (int S = 0; S <= 65535; ++S) {
        for (int i = 0; i <= 15; ++i)
            if (S >> i & 1) f[S] = f[S] * (q[i] - 1ll) % p * ni(q[i]) % p;
        as = (as + f[S]) % p;
    }
    cout << as;
    return 0;
}

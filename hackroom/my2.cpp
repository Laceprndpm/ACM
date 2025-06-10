#include <bits/stdc++.h>
using namespace std;
const long long mod = 1000000007;

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

int main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(false), cin.tie(0);
    int       T;
    long long n, m, k, i, f, x, y, c, c0, c1, cx;
    for (cin >> T; T > 0; T--) {
        cin >> n >> m >> k;
        cx = (n - 2) * 2 + (m - 2) * 2;
        c0 = 0;
        c1 = 0;
        for (i = 0; i < k; i++) {
            cin >> x >> y >> c;
            f = 0;
            if (x == 1) f ^= 1;
            if (x == n) f ^= 1;
            if (y == 1) f ^= 1;
            if (y == m) f ^= 1;
            if (!f) continue;
            if (c == 0) {
                c0++;
                cx--;
            } else {
                c1++;
                cx--;
            }
        }
        if (cx == 0) {
            if (c0 % 2 == 0)
                cout << qpow(2, n * m - k) << '\n';
            else
                cout << "0\n";
        } else
            cout << qpow(2, n * m - k - 1) << '\n';
    }
    return 0;
}
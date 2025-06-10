#include <bits/stdc++.h>
using namespace std;

const int maxn = 5050;
const int mod  = 1000000007;

int  n, a[maxn], fac[maxn], C[maxn][maxn], b[maxn], d[maxn][maxn];
bool vis[maxn];

void solve()
{
    cin >> n;
    for (int i = 0; i <= n; ++i) {
        vis[i] = 0;
        for (int j = 0; j <= n; ++j) {
            d[i][j] = 0;
        }
    }
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        fac[i] = 1LL * fac[i - 1] * i % mod;
        b[i]   = b[i - 1] + (a[i] == -1);
        if (a[i] != -1) {
            vis[a[i]] = 1;
        }
    }
    for (int i = 0; i <= n; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    int mn1 = n;
    for (int i = 1; i <= n; ++i) {
        int mn2 = n;
        for (int j = n; j >= i; --j) {
            int x = b[j] - b[i - 1], y = min(mn1, mn2);
            ++d[x][0];
            --d[x][y];
            if (a[j] != -1) {
                mn2 = min(mn2, a[j]);
            }
        }
        if (a[i] != -1) {
            mn1 = min(mn1, a[i]);
        }
    }
    // learnt!
    for (int i = 0; i <= b[n]; ++i) {
        for (int j = 1; j <= n; ++j) {
            d[i][j] += d[i][j - 1];
        }
    }
    int ans = 0, cnt = 0;
    for (int i = 0; i < n; ++i) {
        cnt += (!vis[i]);
        for (int j = cnt; j <= b[n]; ++j) {
            ans = (ans + 1LL * C[j][cnt] * fac[cnt] % mod * fac[b[n] - cnt] % mod * d[j][i]) % mod;
        }
    }
    // count MEX
    // learnt!
    cout << ans << '\n';
}

int main()
{
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

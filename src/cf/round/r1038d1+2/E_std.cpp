#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using std::cin, std::cout;

#define F(i, a, b)  for (int i = a; i <= (b); ++i)
#define F2(i, a, b) for (int i = a; i < (b); ++i)
#define dF(i, a, b) for (int i = a; i >= (b); --i)

void Solve();

int main()
{
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    int tests = 1;
    cin >> tests;
    while (tests--)
        Solve();
    return 0;
}

using LL      = long long;
const int Mod = 998244353;

const int MN = 505;
const int MK = 505;

int n, k;
int a[4][MN];
int f[MN][MK];

void Solve()
{
    cin >> n >> k;
    for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    for (int j = 0; j <= k; j++)
        f[0][j] = 0;
    f[0][k] = 1;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j <= k; j++)
            f[i][j] = 0;
        
        int t = a[1][i + 1];
        int b = a[2][i];

        auto try_trans = [=](int j, int d, int c) {
            int v = (int)((LL)f[i - 1][j] * c % Mod);
            if (j == k) {
                if (d >= 0)
                    f[i][k] = (f[i][k] + v) % Mod;
                else
                    f[i][-d] = (f[i][-d] + v) % Mod;
            } else {
                if (d >= 0) {
                    if (j >= d) f[i][j - d] = (f[i][j - d] + v) % Mod;
                } else
                    f[i][-d] = (f[i][-d] + v) % Mod;
            }
        };
        // t - b
        if (t != -1 && b != -1) {
            int d = t - b;
            F(j, 0, k)
            {
                if (!f[i - 1][j]) continue;
                try_trans(j, d, 1);
            }
        } else if (t == -1 && b == -1) {
            F(j, 0, k)
            {
                if (!f[i - 1][j]) continue;
                F(d, -(k - 1), k - 1)
                try_trans(j, d, k - std::abs(d));
            }
        } else {
            int lb = t == -1 ? 1 - b : t - k;
            int rb = t == -1 ? k - b : t - 1;
            F(j, 0, k)
            {
                if (!f[i - 1][j]) continue;
                F(d, lb, rb)
                try_trans(j, d, 1);
            }
        }
    }
    int ans = 0;
    F(j, 0, k)
    ans = (ans + f[n - 1][j]) % Mod;
    if (a[1][1] == -1) ans = (int)((LL)ans * k % Mod);
    if (a[2][n] == -1) ans = (int)((LL)ans * k % Mod);
    cout << ans << '\n';
}

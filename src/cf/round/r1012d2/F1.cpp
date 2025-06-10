#include <cstdio>
#include <vector>
#define int long long

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x)
{
    if (x < 0) x = -x, putchar('-');
    if (x / 10) print(x / 10);
    putchar(x % 10 + '0');
}

const int N = (int)5e3 + 5, Mod = (int)1e9 + 7;
int       n, l, k, ans[N], fac[N], facinv[N], inv[N], dp[N], g[N];

int quick_mod(int x, int y)
{
    int s = 1;
    while (y) {
        if (y & 1) s = s * x % Mod;
        x = x * x % Mod;
        y >>= 1;
    }
    return s;
}

void Relax(int& x, int y)
{
    x = x + y >= Mod ? x + y - Mod : x + y;
}

int dist(int i, int j)
{
    if (i < j) return j - i;
    return j + n - i;
}

int dist(int i)
{
    i %= n;
    if (i <= 0) {
        i += n;
    }
    return i;
}

signed main(signed argc, char** argv)
{
    fac[0] = 1;
    for (int i = 1; i < N; ++i)
        fac[i] = fac[i - 1] * i % Mod;
    facinv[N - 1] = quick_mod(fac[N - 1], Mod - 2);
    for (int i = N - 2; i >= 0; --i)
        facinv[i] = facinv[i + 1] * (i + 1) % Mod;
    for (int i = 1; i < N; ++i)
        inv[i] = facinv[i] * fac[i - 1] % Mod;
    int T = init();
    while (T--) {
        n = init(), l = init(), k = init();
        for (int i = 1; i <= n; ++i)
            ans[i] = dp[i] = (l - i + n) / n * inv[l] % Mod;
        for (int turn = l - 1; turn >= 1; --turn) {
            std::vector<int> f(n + 1);
            for (int i = 1; i <= turn; i++) {
                f[dist(i)] += inv[turn];
                f[dist(i)] %= Mod;
            }
            for (int i = 1; i <= n; ++i)
                g[i] = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    // 计算 f[i] 对 g[j] 的贡献
                    // Relax(g[j], (turn - dist(i, j) + n) / n * inv[turn] % Mod * f[i] % Mod);
                    Relax(g[dist(j + i)], f[j] * dp[i] % Mod);
            for (int i = 1; i <= n; ++i)
                Relax(ans[i], dp[i] = g[i]);
        }
        for (int i = 1; i <= n; ++i)
            print(ans[i]), putchar(' ');
        putchar('\n');
    }
}

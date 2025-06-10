#include <cstdio>
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

const int N = (int)2e5 + 5;
int       a[N], s[N];
/*
正常的最大子段和方程是设 dp[i] 表示以 i 结尾的最大子段和
转移是 dp[i] = max{a[i], dp[i-1] + a[i]}，亦可以写作 a[i] + max{0, dp[i-1]}
*/
int dp[N][25];

/*
这里考虑对于每一个 a[i]，不是 -x 就是 +x，那么我们默认每一个 a[i] - x，并对于需要 +x 的 a[i] 进行 +2x
操作，显然不影响贡献 设 dp[i][j] 表示以 i 结尾，使用恰好 j 次 +2x 操作后的最大子段和，注意到 +2x
对最大子段和的贡献只优不劣，因此恰好 j 次即为至多 j 次 转移是
1. 第 i 个位置使用
dp[i][j] = max{a[i] + 2x, dp[i-1][j-1] + a[i] + 2x}
2. 第 i 个位置不使用
dp[i][j] = max{a[i], dp[i-1][j] + a[i]}
*/
int mn(int x, int y)
{
    return x < y ? x : y;
}

int mx(int x, int y)
{
    return x > y ? x : y;
}

void Relax(int& x, int y)
{
    x = mx(x, y);
}

signed main(signed argc, char** argv)
{
    int T = init();
    while (T--) {
        int n = init(), k = init(), x = init();
        if (x >= 0) {
            int min = 0;
            for (int i = 1; i <= n; ++i)
                min = mn(min, a[i] = init() - x);
            int ans = 0;
            for (int i = 1; i <= n; ++i)
                for (int j = 0; j <= mn(k, i); ++j) {
                    dp[i][j] = min;
                    if (j > 0) Relax(dp[i][j], mx(a[i] + 2 * x, dp[i - 1][j - 1] + a[i] + 2 * x));
                    Relax(dp[i][j], mx(a[i], dp[i - 1][j] + a[i]));
                    Relax(ans, dp[i][j]);
                }
            print(ans), putchar('\n');
        } else {
            x       = -x;
            int min = 0;
            for (int i = 1; i <= n; ++i)
                min = mn(min, a[i] = init() + x);
            int ans = 0;
            for (int i = 1; i <= mn(n, k + 1); ++i) {
                // 枚举 i 作为起点
                int j = mn(n, i + n - k - 1);
                // 则终点 j 在这儿
                int curMax = 0, now = 0;
                for (int k = i; k <= j; ++k) {
                    now += a[k];
                    if (now < 0) now = 0;
                    if (now > curMax) curMax = now;
                }
                ans = mx(ans, curMax);
            }
            // 长度 <= n-k 的所有方案
            for (int i = 1; i <= n; ++i)
                s[i] = s[i - 1] + a[i];
            for (int i = 1; i <= n; ++i)
                for (int len = n - k + 1; i + len - 1 <= n; ++len) {
                    int j   = i + len - 1;
                    int out = len - (n - k);
                    ans     = mx(ans, s[j] - s[i - 1] - out * 2 * x);
                }
            print(ans), putchar('\n');
        }
    }
}

#include <cstring>
#include <iostream>
using namespace std;

const int maxp   = 8;
const int maxs   = 1 << maxp;
const int mod    = 12345678;
const int maxrow = 4;
const int maxcol = 7;
const int maxn   = maxrow * maxcol + 2;

int  n, m, ans;
int  f[maxs][maxn], x[maxp], y[maxp], tp;
bool use[maxrow][maxcol];
char graph[maxrow][maxcol];

void init()
{
    scanf("%d%d\n", &n, &m);
    for (int i = 0; i < n; ++i)
        cin >> graph[i];
}

bool in_range(int x, int y)
{
    return x >= 0 && y >= 0 && x < n && y < m;
}

int calc()  // 具体计算
{
    tp = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (graph[i][j] == 'X') x[tp] = i, y[tp++] = j;
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for (int s = 0; s < 1 << tp; ++s) {
        memset(use, 1, sizeof(use));  // use为该点是否可用
        for (int i = 0; i < tp; ++i)
            if (!(s & (1 << i)))
                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy)
                        if (in_range(x[i] + dx, y[i] + dy)) use[x[i] + dx][y[i] + dy] = 0;

        int cnt = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (use[i][j]) ++cnt;  // 当前s状态，最多能放cnt个

        for (int i = 0; i <= cnt; ++i)
            if (f[s][i]) {
                f[s][i + 1] = (f[s][i + 1] + f[s][i] * (cnt - i)) % mod;
                // 放一个点，有cnt个空可选吗？
                // 哦哦，没事的，因为下面一个转移保证了你每次放的时候，必然i++，所以不会出现'.'放的比相邻的'x'早的情况
                for (int j = 0; j < tp; ++j)
                    if (!(s & (1 << j))) f[s | (1 << j)][i + 1] = (f[s | (1 << j)][i + 1] + f[s][i]) % mod;
            }
    }
    return f[(1 << tp) - 1][n * m];
}

void search(int x, int y, int k)
{
    if (x >= n)
        ans = (ans + k * calc()) % mod;
    else if (y >= m)
        search(x + 1, 0, k);
    else {
        search(x, y + 1, k);
        bool ok = 1;                      // 该点可以放一个额外的'X'
        for (int dx = -1; dx <= 1; ++dx)  // 对该点3x3范围搜索，如果已经有 'X' 则ok = 0
            for (int dy = -1; dy <= 1; ++dy)
                if (in_range(x + dx, y + dy) && graph[x + dx][y + dy] == 'X') ok = 0;
        if (ok) {
            graph[x][y] = 'X';     // 放下，以枚举超集
            search(x, y + 1, -k);  // 反转容斥系数
            graph[x][y] = '.';
        }
    }
}

int solve()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (graph[i][j] == 'X')
                for (int dx = -1; dx <= 1; ++dx)
                    for (int dy = -1; dy <= 1; ++dy)
                        if ((dx || dy) && in_range(i + dx, j + dy) && graph[i + dx][j + dy] == 'X') return 0;
    ans = 0;
    search(0, 0, 1);
    return (ans + mod) % mod;
}

int main()
{
    init();
    printf("%d\n", solve());

    return 0;
}

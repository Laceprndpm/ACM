// T566659 分组背包
// TODO
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x / 10)
        print(x / 10);
    putchar(x % 10 + '0');
}

std::vector<std::pair<int, int>> G[10];
const int                        N = (int)1e5 + 5, lim = 1000;
int                              n, m, c[N][10];
int                              vis[N];

bool check(int mid)
{
    // 仅购买性价比高于 mid 的物品时，是否能装满背包
    memset(vis, false, sizeof(vis));
    int V = 0;
    for (int j = 9; j >= 0; --j)
        for (int i = n - 1; i >= 0; --i) {
            if (G[j][i].first < mid * (j + 1))
                break;
            int who = G[j][i].second;
            if (vis[who])
                continue;
            bool flag = true;
            for (int k = j - 1; k >= 0 && flag; --k)
                // 将 c[j] 与 c[k] 作比较
                if (c[who][j] - c[who][k] < mid * (j - k))
                    flag = false;
            if (flag) {
                vis[who] = j + 1;
                V += (j + 1);
            }
        }
    return V + lim >= m;
}

int dp[N];

int mx(int x, int y)
{
    return x > y ? x : y;
}

signed main(signed argc, char** argv)
{
// #define BATCH
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    n = init(), m = init();
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 10; ++j) {
            c[i][j] = init();
            G[j].push_back(std::make_pair(c[i][j], i));
            // 重量为 j+1 的物品，价值集合为 c[j]
        }
    for (int j = 0; j < 10; ++j)
        std::stable_sort(G[j].begin(), G[j].end());
    int ans = 0;
    if (m > lim) {
        int L = 1, R = (int)1e9;
        while (L < R - 5) {
            int mid = L + R >> 1;
            if (check(mid))
                L = mid + 1;
            else
                R = mid;
        }
        int mid;
        for (int i = L; i <= R; ++i)
            if (!check(i)) {
                mid = i;
                break;
            }
        memset(vis, false, sizeof(vis));
        int V = 0;
        for (int j = 9; j >= 0; --j)
            for (int i = n - 1; i >= 0; --i) {
                if (G[j][i].first < mid * (j + 1))
                    break;
                int who = G[j][i].second;
                if (vis[who])
                    continue;
                bool flag = true;
                for (int k = j - 1; k >= 0 && flag; --k)
                    // 将 c[j] 与 c[k] 作比较
                    if (c[who][j] - c[who][k] < mid * (j - k))
                        flag = false;
                if (flag) {
                    vis[who] = j + 1;
                    m -= (j + 1);
                    ans += G[j][i].first;
                }
            }
    }
    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            for (int w = m; w >= 1; --w)
                for (int j = 0; j < 10; ++j)
                    if (w >= j + 1)
                        dp[w] = mx(dp[w], dp[w - (j + 1)] + c[i][j]);
                    else
                        break;
        } else {
            for (int w = m; w >= 1; --w)
                for (int j = vis[i] + 1; j <= 10; ++j)
                    if (w >= (j - vis[i]))
                        dp[w] = mx(dp[w], dp[w - (j - vis[i])] - c[i][vis[i] - 1] + c[i][j - 1]);
                    else
                        break;
        }
    int max = 0;
    for (int i = 1; i <= m; ++i)
        max = mx(max, dp[i]);
    print(ans + max), putchar('\n');
    return 0;
}
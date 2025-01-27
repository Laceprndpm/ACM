#include <algorithm>
#include <cstdint>
#include <cstdio>
#define int long long
constexpr int N = (int)1e6 + 5;

int  n, k, dp[N];
bool vis[N];

int init() {
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x / 10)
        print(x / 10);
    putchar(x % 10 + '0');
}

int mn(int x, int y) {
    return x < y ? x : y;
}

int l[N], r[N];

signed main(signed argc, char** argv) {
    freopen("A00.in", "r", stdin);
    // freopen("A00.out", "w", stdout);
    int T = init();
    while (T--) {
        int n = init(), k = init();
        for (int i = 1; i <= n; ++i) {

            l[i] = init(), r[i] = init() - 1;
        }

        if (r[n] >= N) {
            puts("0");
            continue;
        }

        for (int i = 0; i <= r[n]; ++i) {
            dp[i] = INT32_MAX, vis[i] = false;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = l[i]; j <= r[i]; ++j)
                vis[j] = true;
        }

        dp[0] = 0;
        for (int i = 1; i <= r[n]; ++i) {
            bool peopleInMid = vis[i];
            for (int j = 1; j <= std::min(i, k); ++j) {
                dp[i] = mn(dp[i], dp[i - j] + (peopleInMid ? 1 : 0));
                peopleInMid |= vis[i - j];
            }
        }

        print(dp[r[n]]), putchar('\n');
    }
}

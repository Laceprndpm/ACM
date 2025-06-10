#include <cstdio>
#include <queue>
#include <vector>
#define int long long

/**
 *@Spell : greedy, regret greedy
 */

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
int       d[N];

signed main(signed argc, char** argv)
{
    int T = init();
    while (T--) {
        int n = init(), k = init();
        for (int i = 1; i <= n; ++i)
            d[i] = init();
        std::priority_queue<int, std::vector<int>, std::greater<int>> Q;

        int s = 0, ans = 0;
        for (int i = n; i >= 1; --i)
            if (s >= k) {  // choose
                s -= k;
                ans += d[i];
                Q.push(d[i]);
            } else {
                if (Q.empty() || d[i] <= Q.top()) {  // 无法选择，或者Q为空
                    s++;
                    continue;
                }
                s += (k + 1);
                ans -= Q.top();
                Q.pop();
                s -= k;
                ans += d[i];
                Q.push(d[i]);
            }
        print(ans), putchar('\n');
    }
}

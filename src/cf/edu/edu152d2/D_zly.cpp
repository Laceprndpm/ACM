#include <cstdio>

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
int       a[N], b[N];

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n = init();
    for (int i = 1; i <= n; ++i)
        a[i] = init();
    for (int i = 1; i <= n; ++i)
        if (a[i] == 0)
            b[++b[0]] = 0;
        else {
            bool flag = false;
            for (int j = i; a[j] != 0; ++j)
                flag |= (a[i = j] == 2);
            if (flag)
                b[++b[0]] = 2;
            else
                b[++b[0]] = 1;
        }
    int ans = 0;
    for (int i = 2; i < b[0]; ++i)
        if (b[i] == 2 && (b[i - 1] == 0 || b[i + 1] == 0)) ++ans, b[i - 1] = b[i + 1] = 1;
    for (int i = 1; i <= b[0]; ++i)
        ans += !b[i];
    print(ans == 0 ? 1 : ans), putchar('\n');
}
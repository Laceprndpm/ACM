#include <cstdio>

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

const int N = (int)5e5 + 5;
int       b[N];
bool      lock[N];

int ab(int x)
{
    return x < 0 ? -x : x;
}

signed main(signed argc, char** argv)
{
#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int m = init(), k = init();
    for (int i = 1; i <= m; ++i)
        b[i] = init();
    int n = init(), lastans = 0;
    while (n--) {
        int a = init() ^ lastans;
        for (int i = 1; i <= m; ++i)
            if (ab(a - b[i]) <= k && !lock[i])
                lock[i] = true, ++lastans;
        print(lastans), putchar('\n');
    }
    return 0;
}
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
bool      vis[N];

signed main(signed argc, char** argv)
{
    int n = init();
    for (int i = 1; i <= n; ++i)
        a[i] = init();
    for (int i = 1; i <= n; ++i) {
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
    }
    int ans = 0;
    for (int i = 2; i < b[0]; ++i)
        if (b[i] == 2 && (b[i - 1] == 0 || b[i + 1] == 0)) {
            ++ans;
            vis[i - 1] = vis[i] = vis[i + 1] = true;
        }
    // 一步解 3 个
    for (int i = 1; i <= b[0]; ++i) {
        if (i > 1 && b[i] >= 1 && b[i - 1] == 0 && !vis[i] && !vis[i - 1]) {
            ++ans;
            vis[i - 1] = vis[i] = true;
        }
        if (i < b[0] && b[i] >= 1 && b[i + 1] == 0 && !vis[i] && !vis[i + 1]) {
            ++ans;
            vis[i] = vis[i + 1] = true;
        }
    }
    // 一步解 2 个
    for (int i = 1; i <= b[0]; ++i)
        ans += !vis[i];
    // 一步解 1 个
    print(ans), putchar('\n');
}
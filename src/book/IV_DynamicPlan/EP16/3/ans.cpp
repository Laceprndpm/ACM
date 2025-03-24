#include <bits/stdc++.h>
#define maxn 1000
using namespace std;
int n, m, f[maxn][maxn], head[maxn], cnt;

struct edge {
    int to, pre;
} e[maxn];

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-') f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void add(int from, int to)
{
    e[++cnt].pre = head[from];
    e[cnt].to    = to;
    head[from]   = cnt;
}

void DFS(int now)
{
    //    f[now][0]=0;
    for (int i = head[now]; i; i = e[i].pre) {
        int go = e[i].to;
        DFS(go);
        for (int j = m + 1; j >= 1; j--) {
            for (int k = 0; k < j; k++) {
                f[now][j] = max(f[now][j], f[go][k] + f[now][j - k]);
            }
        }
    }
}

int main()
{
    n = init(), m = init();
    for (int i = 1; i <= n; i++) {
        int fa  = init();
        f[i][1] = init();
        add(fa, i);
    }
    DFS(0);
    printf("%d\n", f[0][m + 1]);
    return 0;
}
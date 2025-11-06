#include <cstdio>
using namespace std;

int       n, m, q, fa[100005][65], b[65];
long long V;

int find(int x, int i) { return x == fa[x][i] ? x : fa[x][i] = find(fa[x][i], i); }

int main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    scanf("%d%d%d%lld", &n, &m, &q, &V);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= 61; ++j) fa[i][j] = i;
    for (int j = 60; ~j; --j)
        if (V & (1ll << j)) b[j] = 1;
    for (int i = 1; i <= m; ++i) {
        int       u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        for (int j = 60; ~j; --j) {
            bool f = (w & (1ll << j));
            if ((!b[j]) && f)
                fa[find(u, j)][j] = find(v, j);
            else if (b[j] && (!f))
                break;
        }
        if ((w & V) >= V) fa[find(u, 61)][61] = find(v, 61);
    }
    for (int i = 1; i <= q; ++i) {
        int u, v, flag = 0;
        scanf("%d%d", &u, &v);
        for (int j = 61; ~j; --j)
            if (find(u, j) == find(v, j)) {
                flag = 1;
                break;
            }
        puts(flag ? "Yes" : "No");
    }
    return 0;
}

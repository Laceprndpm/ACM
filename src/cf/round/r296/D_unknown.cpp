#include <bits/stdc++.h>
#define N 200002
using namespace std;
int       n, m, k, s[N][4], c[501];
bitset<N> b[4], ans;
char      A[N], B[N];

signed main(void)
{
    int i, j;
    scanf("%d%d%d%s%s", &n, &m, &k, A + 1, B + 1), c['A'] = 0, c['G'] = 1, c['C'] = 2, c['T'] = 3;
    for (i = 1; i <= n; ++i) ++s[max(1, i - k)][c[A[i]]], --s[min(n + 1, i + k + 1)][c[A[i]]];
    for (i = 1; i <= n; ++i) {
        for (ans[i] = 1, j = 0; j < 4; ++j) {
            s[i][j] += s[i - 1][j];
            if (s[i][j]) b[j][i] = 1;
        }
    }
    // 对于模式串来说，i位为A，那么若k位可以作为开头，则s>>i也的为A
    for (i = 1; i <= m; ++i) ans &= (b[c[B[i]]] >> (i - 1));
    printf("%d\n", ans.count());
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

constexpr int maxn = 66;
int           m, sum, mn = maxn, mx, d;
int           len[maxn], a[maxn], pre[maxn];

void dfs(int u, int k, int p)
{
    if (u == 0) {
        dfs(d, k - 1, a[m]);
        return;
    }
    if (k == 0) {
        printf("%d\n", d);
        exit(0);
    }
    p = (p < u) ? p : u;
    while (p && len[p] == 0)
        --p;
    while (p) {
        if (len[p]) {
            --len[p];
            dfs(u - p, k, p);
            ++len[p];
            if ((u == p) || (u == d)) {
                return;
            }
            p = pre[p];
        } else {
            p = pre[p];
        }
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        sum += x;
        ++len[a[i] = x];
    }
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (a[i] != a[i - 1]) {
            pre[a[i]] = a[i - 1];
        }
    }
    for (d = a[n]; (d << 1) <= sum; ++d) {
        if ((sum % d) == 0) {
            dfs(d, sum / d, a[n]);
        }
    }
    printf("%d\n", sum);
    return 0;
}
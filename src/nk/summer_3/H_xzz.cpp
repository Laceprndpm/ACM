#include <bits/stdc++.h>

#include <random>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
#define endl '\n'
using pll   = pair<ll, ll>;
using pii   = pair<int, int>;
const int N = 1e6 + 10;
mt19937   rnd(114514);
// #define int ll
#define ls (k + k)
#define rs (k + k + 1)
vector<int> g[N];
int         fa[N][21];
int         sz[N], dfn[N], idx, dep[N];

void dfs(int u)
{
    dfn[u] = ++idx;
    dep[u] = dep[fa[u][0]] + 1;
    sz[u]  = 1;
    for (auto v : g[u]) {
        if (v == fa[u][0]) continue;
        dfs(v);
        sz[u] += sz[v];
    }
}

struct quiry {
    int u, l, r;
} Q[N];

int a[N];

int get(int u, int k)
{
    for (int i = 20; i >= 0; i--) {
        if ((k >> i) & 1) u = fa[u][i];
    }
    return u;
}

void UraykevoliQwQ()
{
    int n, k;
    cin >> n >> k;
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        fa[i][0] = x;
        for (int j = 1; j <= 20; j++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        g[i].push_back(x);
        g[x].push_back(i);
    }
    vector<int> t(n + 10, 0);
    dfs(1);
    auto add = [&](int pos, int val) {
        if (pos < 1 || pos > n) return;
        for (int i = pos; i <= n; i += i & -i)
            t[i] += val;
    };
    auto cal = [&](int pos) {
        if (pos < 1 || pos > n) return 0;
        int res = 0;
        for (int i = pos; i >= 1; i -= i & -i)
            res += t[i];
        return res;
    };
    for (int i = 1; i <= k; i++) {
        cin >> Q[i].u >> Q[i].l >> Q[i].r;
    }
    for (int i = 1; i <= k; i++) {
        int u = Q[i].u, l = Q[i].l, r = Q[i].r;
        int dis = dep[u] - 1, len = r - l + 1;
        int rest = cal(dfn[u]);
        rest     = max(rest - 1, 0);
        int tot  = dis - rest;
        if (tot == 0) {
            cout << l << endl;
            return;
        } else if (len >= tot) {
            cout << l + tot - 1;
            return;
        }
        int v = get(u, dis - rest - len);
        while (v && !a[v]) {
            a[v] = 1;
            add(dfn[v], 1);
            add(dfn[v] + sz[v], -1);
            v = fa[v][0];
        }
    }
    cout << -1 << endl;
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _ = 1;
    // cin >>_;
    while (_--)
        UraykevoliQwQ();
    // return 0;
}

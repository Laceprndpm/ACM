#include <bits/stdc++.h>

#include <random>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
#define endl '\n'
using pll   = pair<ll, ll>;
using pii   = pair<int, int>;
const int N = 2e6 + 10;
mt19937   rnd(114514);
ll        X[N];
#define int ll
const ll p = 998244353;
int      fa[N], sz[N], pre[N];

int find(int x)
{
    return pre[x] == x ? x : pre[x] = find(pre[x]);
}

void UraykevoliQwQ()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        pre[i] = i, sz[i] = 1;
    int k = 0;
    while (q--) {
        ll a, b, c;
        cin >> a >> b >> c;
        ll  A  = 1 + (((a * (1 + X[k])) % p) % 2);
        ll  B  = 1 + (((b * (1 + X[k])) % p) % n);
        ll  C  = 1 + (((c * (1 + X[k])) % p) % n);
        int op = A, u = B, v = C;
        // int op, u, v; cin >> op >> u >> v;
        if (op == 1) {
            if (sz[find(u)] > sz[find(v)]) swap(u, v);
            for (int i = u, j = v; i;) {
                int tmp = fa[i];
                fa[i]   = j;
                j = i, i = tmp;
            }
            pre[find(u)] = find(v);
            sz[find(v)] += sz[find(u)];
        } else {
            int ans = 0;
            if (fa[fa[u]] == v)
                ans = fa[u];
            else if (fa[u] == fa[v])
                ans = fa[u];
            else if (fa[fa[v]] == u)
                ans = fa[v];
            X[++k] = ans;
            cout << ans << endl;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while (_--)
        UraykevoliQwQ();
    // return 0;
}
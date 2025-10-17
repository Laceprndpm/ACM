#include <bits/stdc++.h>

#include <random>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
#define endl '\n'
using pll   = pair<ll, ll>;
using pii   = pair<int, int>;
const int N = 6e5 + 10;
mt19937   rnd(114514);
#define int ll
#define ls  (k + k)
#define rs  (k + k + 1)
int         a[N], b[N];
vector<int> g[N];
int         dep[N], ans[N], f1[N], f2[N];
bool        vis[N];
pii         e[N];

int cal(int u, int x) { return a[u] - b[u] * (dep[u] - x); }

void dfs(int u)
{
    if (vis[u]) return;
    vis[u] = 1;
    for (auto v : g[u]) {
        dfs(v);
        f1[u] = max({f1[u], f1[v], f2[v]});
    }
}

void UraykevoliQwQ()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        e[i] = {u, v};
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 2; i <= n; i++) dep[i] = -1;
    queue<int> q;
    q.push(1);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (dep[v] == -1) {
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
    }
    int max1 = -1e18, max2 = -1e18;
    for (int i = 1; i <= n; i++) {
        if (cal(i, -1) > max1) {
            max2 = max1;
            max1 = cal(i, -1);
        } else if (cal(i, -1) > max2) {
            max2 = cal(i, -1);
        }
    }

    for (int i = 1; i <= n; i++) {
        g[i].clear();
        f1[i] = f1[i + n] = -1e18;
        f2[i]             = cal(i, 1);
        f2[i + n]         = cal(i, 0);
    }
    for (int i = 1; i <= m; i++) {
        int u = e[i].first, v = e[i].second;
        if (dep[u] == dep[v]) {
            g[u].push_back(v + n);
            g[v].push_back(u + n);
        } else {
            if (dep[u] > dep[v]) swap(u, v);
            g[u].push_back(v);
            g[u + n].push_back(v + n);
        }
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        if (dep[i] == 1) {
            if (cal(i, -1) == max1) {
                cout << max(f1[i], max2) << endl;
            } else {
                cout << max(f1[i], max1) << endl;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int _ = 1;
    // cin >>_;
    while (_--) UraykevoliQwQ();
    // return 0;
}
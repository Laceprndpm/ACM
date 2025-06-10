#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;
const int N = 2e6 + 10;
using ll    = long long;
using pii   = pair<int, int>;
using pll   = pair<ll, ll>;
#define endl '\n'
#define ls   (k + k)
#define rs   (k + k + 1)

// #define int ll
struct Q {
    int u, v, ans;
} q[100010];

int           sz[100010], pre[100010];
map<pii, int> mp;

struct edge {
    int u, v, c;
} e[100010];

struct add {
    int u, v, fu, fv;
};

stack<add> st;

int find(int x)
{
    return pre[x] == x ? x : find(pre[x]);
}

void merge(int u, int v)
{
    int fu = find(u), fv = find(v);
    st.push({u, v, fu, fv});
    if (fu == fv) return;
    if (sz[fu] > sz[fv]) swap(fu, fv);
    pre[fu] = fv;
    sz[fv] += sz[fu];
}

bool vis[100010];

void sub()
{
    int u = st.top().u, v = st.top().v, fu = st.top().fu, fv = st.top().fv;
    st.pop();
    if (fu == fv) return;
    if (sz[fu] > sz[fv]) swap(fu, fv);
    pre[fu] = fu;
    sz[fv] -= sz[fu];
}

void Uraykevoli()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        sz[i] = 1, pre[i] = i;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        e[i] = {u, v, c};
    }
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        cin >> q[i].u >> q[i].v;
        vis[q[i].u] = vis[q[i].v] = 1;
    }
    sort(e + 1, e + m + 1, [&](const edge& x, const edge& y) {
        return x.c < y.c;
    });
    vector<int> a;
    int         sq = sqrt(m);
    int         l  = 1;
    while (l <= m) {
        a.clear();
        int r = l;
        while (e[r + 1].c == e[l].c)
            r++;
        for (int i = l; i <= r; i++)
            a.push_back(e[i].u), a.push_back(e[i].v);
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        for (int i = l; i <= r; i++) {
            int u = e[i].u, v = e[i].v;
            merge(u, v);
        }
        if (a.size() >= sq) {
            for (int i = 1; i <= t; i++) {
                int u = q[i].u, v = q[i].v;
                if (find(u) == find(v)) q[i].ans++;
            }
        } else {
            for (auto u : a) {
                for (auto v : a) {
                    if (!vis[u] || !vis[v]) continue;
                    if (find(u) == find(v)) mp[{u, v}]++;
                }
            }
        }
        while (st.size())
            sub();
        l = r + 1;
    }
    for (int i = 1; i <= t; i++) {
        cout << q[i].ans + mp[{q[i].u, q[i].v}] << endl;
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    // cin >> _;
    while (_--)
        Uraykevoli();
    // return 0;
}
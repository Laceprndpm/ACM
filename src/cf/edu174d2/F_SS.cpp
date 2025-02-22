#include <bits/stdc++.h>
using namespace std;
const int                                        tdep = 19;
int                                              ans[1 << 19][2], cans;
vector<int>                                      lvec[1 << 20][2], opv;
int                                              fa[400000], siz[400000];
map<tuple<long long, long long, long long>, int> mp;
int                                              op[400000][3];
string                                           s;

int combine(int x, int y)
{
    while (x != fa[x])
        x = fa[x];
    while (y != fa[y])
        y = fa[y];
    if (x == y)
        return 0;
    if (siz[x] > siz[y])
        swap(x, y);
    opv.push_back(x);
    fa[x] = y;
    siz[y] += siz[x];
    cans--;
    return 1;
}

void rd()
{
    int x = opv[(int)opv.size() - 1], y;
    y     = fa[x];
    fa[x] = x;
    siz[y] -= siz[x];
    cans++;
    opv.pop_back();
}

void add(int t, int dep, int l, int r, int u, int v)
{
    if (l == 0 && r == (1 << dep)) {
        lvec[t][0].push_back(u);
        lvec[t][1].push_back(v);
        return;
    }
    int x = (1 << (dep - 1));
    if (l < x) {
        if (r <= x)
            add(t * 2 + 1, dep - 1, l, r, u, v);
        else {
            add(t * 2 + 1, dep - 1, l, x, u, v);
            add(t * 2 + 2, dep - 1, 0, r - x, u, v);
        }
    } else
        add(t * 2 + 2, dep - 1, l - x, r - x, u, v);
}

void dfs(int t, int dep, int p, int tag)
{
    int c = 0, i;
    for (i = 0; i < lvec[t][0].size(); i++)
        c += combine(lvec[t][0][i], lvec[t][1][i]);
    if (dep == 0)
        ans[p][tag] = cans;
    else {
        dfs(t * 2 + 1, dep - 1, p, tag);
        dfs(t * 2 + 2, dep - 1, p + (1 << (dep - 1)), tag);
    }
    while (c > 0) {
        rd();
        c--;
    }
}

void solve(int n, int q, int tag)
{
    long long                                                  i, u, v, p, d = 1000000000;
    map<tuple<long long, long long, long long>, int>::iterator it;
    for (i = 0; i < q; i++) {
        p = op[i][0];
        if (p > tag)
            continue;
        u = op[i][1];
        v = op[i][2];
        if (u > v)
            swap(u, v);
        if (mp.find({p, u, v}) == mp.end())
            mp[{p, u, v}] = i;
        else {
            add(0, tdep, mp[{p, u, v}], i, u, v);
            mp.erase({p, u, v});
        }
    }
    for (it = mp.begin(); it != mp.end(); it++) {
        auto [_, u, v] = (*it).first;
        add(0, tdep, (*it).second, q, u, v);
    }
    mp.clear();
    for (i = 0; i < n; i++) {
        fa[i]  = i;
        siz[i] = 1;
    }
    cans = n;
    dfs(0, tdep, 0, tag);
    for (i = 0; i < (1 << 20); i++) {
        lvec[i][0].clear();
        lvec[i][1].clear();
    }
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int n, q, i, u, v;
    cin >> n >> q;
    for (i = 0; i < q; i++) {
        cin >> s >> op[i][1] >> op[i][2];
        op[i][1]--;
        op[i][2]--;
        if (s == "A")
            op[i][0] = 0;
        else
            op[i][0] = 1;
    }
    solve(n, q, 0);
    solve(n, q, 1);
    for (i = 0; i < q; i++)
        cout << ans[i][0] - ans[i][1] << '\n';
    return 0;
}
#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

struct edge {
    int u, w;
};

int                  n;
vector<vector<edge>> g;
vector<vector<int>>  ng;
vector<int>          tin, tout, siz, ord;
int                  T;

vector<int> pw;

void init(int v, int p = -1)
{
    tin[v] = T++;
    ord.push_back(v);
    siz[v] = 1;
    for (const auto &it : g[v]) {
        int u = it.u, w = it.w;
        if (u == p) continue;
        pw[u] = w;
        init(u, v);
        siz[v] += siz[u];
    }
    tout[v] = T;
}

int isp(int v, int u)
{
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

vector<int>         nsiz;
vector<vector<int>> dp;

long long dfs(int v, int x)
{
    long long res = 0;
    for (int u : ng[v])
        res += dfs(u, x);
    dp[v][0] = siz[v];
    dp[v][1] = 0;
    for (int u : ng[v])
        dp[v][0] -= siz[u];
    for (int u : ng[v]) {
        if (pw[u] == x) {
            res += dp[u][0] * 1ll * dp[v][0];
            dp[v][1] += dp[u][0];
        } else {
            res += dp[u][0] * 1ll * dp[v][1];
            res += dp[u][1] * 1ll * dp[v][0];
            dp[v][0] += dp[u][0];
            dp[v][1] += dp[u][1];
        }
    }
    return res;
}

int main()
{
    scanf("%d", &n);

    g.resize(n);
    forn(i, n - 1)
    {
        int v, u, w;
        scanf("%d%d%d", &v, &u, &w);
        --v, --u, --w;
        g[v].push_back({u, w});
        g[u].push_back({v, w});
    }

    T = 0;
    tin.resize(n);
    tout.resize(n);
    siz.resize(n);
    pw.resize(n, -1);
    init(0);

    vector<vector<int>> sv(n, vector<int>(1, 0));
    for (int v : ord)
        for (auto it : g[v])
            sv[it.w].push_back(v);

    ng.resize(n);
    nsiz.resize(n);
    dp.resize(n, vector<int>(2));
    long long ans = 0;
    forn(i, n) if (!sv[i].empty())
    {
        sv[i].resize(unique(sv[i].begin(), sv[i].end()) - sv[i].begin());
        vector<int> st;
        for (int v : sv[i]) {
            while (!st.empty() && !isp(st.back(), v))
                st.pop_back();
            if (!st.empty()) ng[st.back()].push_back(v);
            st.push_back(v);
        }
        ans += dfs(0, i);

        ng[0].clear();
    }

    printf("%lld\n", ans);
    return 0;
}
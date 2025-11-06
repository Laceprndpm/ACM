#include <bits/stdc++.h>

#include <vector>
using namespace std;
using i64 = long long;
#define fi first
#define se second
#define pb push_back

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> isfrind(k + 1);
    for (int i = 1, has; i <= n; i++) {
        cin >> has;
        isfrind[has] = 1;
    }
    vector<vector<int>> go(k + 1);
    int                 baseans = 0;
    vector<int>         bounds(k + 1);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (u > v) swap(u, v);
        if (isfrind[u] && isfrind[v]) {
            baseans++;
        } else if (isfrind[u]) {
            bounds[v]++;
        } else if (isfrind[v]) {
            bounds[u]++;
        } else if (u == v) {
            bounds[u]++;
        } else {
            go[u].pb(v);
        }
    }
    if (n + 2 >= k) {
        cout << m << '\n';
        return;
    }
    i64         ans = 0;
    vector<int> peoplecnt(m + 2);  // 每个贡献对应人数
    for (int i = 1; i <= k; i++) peoplecnt[bounds[i]]++;
    int curmax = m + 1;
    while (peoplecnt[curmax] == 0) curmax--;
    auto update = [&](int u, int val) {
        peoplecnt[bounds[u]]--;
        bounds[u] += val;
        peoplecnt[bounds[u]]++;
        if (peoplecnt[curmax + 1] >= 1) curmax++;
        if (peoplecnt[curmax] == 0) curmax--;
    };
    for (int i = 1; i <= k; i++) {
        i64 cur = bounds[i];
        peoplecnt[cur]--;
        int bak = curmax;
        while (peoplecnt[curmax] == 0) curmax--;
        for (int v : go[i]) update(v, 1);
        ans = max(ans, baseans + cur + curmax);
        for (int v : go[i]) update(v, -1);
        peoplecnt[cur]++;
        curmax = bak;
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
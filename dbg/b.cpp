#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, q;
    cin >> n >> q;
    vector<int>         fa(n + 1);
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        fa[i] = x;
        adj[x].push_back(i);
    }
    vector<int>         siz(n + 1);
    vector<int>         weight(n + 1);
    vector<int>         ans(n + 1);
    function<void(int)> dfs = [&](int cur) -> void {
        siz[cur]    = 1;
        weight[cur] = 0;
        ans[cur]    = cur;
        for (auto x : adj[cur]) {
            dfs(x);
            siz[cur] += siz[x];
            weight[cur] = max(weight[cur], siz[x]);
        }
        for (auto x : adj[cur]) {
            int p = ans[x];
            while (p != cur) {
                if (max(weight[p], siz[cur] - siz[p]) <= siz[cur] / 2) {
                    ans[cur] = p;
                    break;
                } else
                    p = fa[p];
            }
        }
    };
    dfs(1);
    while (q--) {
        int x;
        cin >> x;
        cout << ans[x] << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--)
        Echo2();
}
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

#define pb push_back

constexpr ll INF = 1e16;

void solve()
{
    int n;
    cin >> n;
    vector<ll>          val(n + 1);
    vector<vector<int>> sons(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 2; i <= n; i++) {
        int v;
        cin >> v;
        sons[v].pb(i);
    }
    auto dfs = [&](auto&& self, int u) -> ll {
        if (sons[u].size() == 0) {
            return val[u];
        }
        ll mnsons = INF;
        for (int v : sons[u]) {
            mnsons = min(mnsons, self(self, v));
        }
        return min((mnsons + val[u]) / 2, mnsons);
    };
    ll allsons = INF;
    for (int v : sons[1]) {
        allsons = min(allsons, dfs(dfs, v));
    }
    cout << allsons + val[1] << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> bi(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> bi[i];
    }
    vector<vector<pair<int, int>>> from(n + 1);
    vector<vector<pair<int, int>>> to(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        from[v].push_back({u, w});
        to[u].push_back({v, w});
    }
    function<bool(int)> check = [&](int x) -> bool {
        vector<int> maxn(n + 1, -1);
        maxn[1] = 0;
        for (int i = 1; i <= n; i++) {
            if (maxn[i] == -1) continue;
            maxn[i] = min(maxn[i] + bi[i], x);
            for (auto [adj, w] : to[i]) {
                if (w <= maxn[i]) {
                    maxn[adj] = max(maxn[i], maxn[adj]);
                }
            }
        }
        return maxn[n] != -1;
    };
    i64 l = 0, r = 1e9;
    if (!check(r)) {
        cout << -1 << '\n';
        return;
    }
    i64 ans;
    while (l <= r) {
        i64 mid = (r + l) / 2;
        if (check(mid)) {
            ans = mid;
            r   = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    // vector<int>                    ls_need(n + 1, INF);
    // vector<int>                    max_ele(n + 1, INF);
    // ls_need[n] = 0;
    // max_ele[n] = 0;
    // for (int i = n; i >= 1; i--) {
    //     for (auto [f, w] : from[i]) {
    //         ls_need[f] = min(ls_need[f], max(w, ls_need[i] - bi[i]));
    //         // max_ele[f] = min(max_ele[f], max({w, ls_need[f], max_ele[i]}));
    //     }
    // }
    // vector<int> maxn(n + 1);
    // for (int i = 1; i <= n; i++) {
    //     maxn[i] += bi[i];
    //     for (auto [s, w] : to[i]) {
    //         maxn[i]
    //     }
    // }
    // if (ls_need[1] <= bi[1]) {
    //     cout << max_ele[1] << '\n';
    //     // for (int i = 1; i <= n; i++) {
    //     //     for (auto [f, w] : from[i]) {
    //     //         ls_need[f] = min(ls_need[f], max(w, ls_need[i]));
    //     //     }
    //     // }
    // } else {
    //     cout << -1 << '\n';
    // }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
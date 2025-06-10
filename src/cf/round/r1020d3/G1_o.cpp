#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, rt;
    cin >> n >> rt;
    vector<int> node(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> node[i];
    }
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int>           father(n + 1);
    function<void(int u)> dfs = [&](int u) -> void {
        for (int adj : graph[u]) {
            if (adj == father[u]) continue;
            father[adj] = u;
            dfs(adj);
        }
    };
    father[rt] = rt;
    dfs(rt);
    while (true) {
        string cmd;
        cin >> cmd;
        if (cmd == "?") {
            int cmd2;
            cin >> cmd2;
            if (cmd2 == 1) {
                int k;
                cin >> k;
                i64 ans = 0;
                for (int i = 0; i < k; i++) {
                    int u;
                    cin >> u;
                    while (father[u] != u) {
                        ans += node[u];
                        u = father[u];
                    }
                    ans += node[u];
                }
                cout << ans << endl;
            } else {
                int k;
                cin >> k;
                node[k] = -node[k];
            }
        }
    }
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
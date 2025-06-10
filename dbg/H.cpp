#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define int i64

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n + 1);
    vector<bool>                   vis(n + 1);
    vector<int>                    dist(n + 1);
    for (int i = 0; i < m; i++) {
        int ai, bi, ci;
        cin >> ai >> bi >> ci;
        graph[ai].push_back({bi, ci});
        graph[bi].push_back({ai, -ci});
    }
    bool                ok  = true;
    function<void(int)> dfs = [&](int cur) -> void {
        if (vis[cur]) return;
        vis[cur] = true;
        for (const auto& [adj, w] : graph[cur]) {
            if (vis[adj]) {
                if (dist[cur] + w != dist[adj]) {
                    ok = false;
                    return;
                }
            } else {
                dist[adj] = w + dist[cur];
                dfs(adj);
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        dfs(i);
    }
    if (ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> wArr(n + 1);
    vector<int> dfsn(n + 1);
    vector<int> outDfsn(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> wArr[i];
    }
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<int> wdfsn(n + 1);
    {
        int                 t   = 0;
        function<void(int)> dfs = [&](int u) {
            dfsn[u] = ++t;
            for (int adj : graph[u]) {
                if (dfsn[adj] != 0) continue;
                dfs(adj);
            }
            outDfsn[u] = t;
        };
        dfs(1);
    }
    for (int i = 1; i <= n; i++) {
        wdfsn[dfsn[i]] = wArr[i];
    }
    vector<int> prefix(n + 2);
    vector<int> suffix(n + 2);
    for (int i = 1; i <= n; i++) {
        prefix[i + 1] = max(prefix[i], wdfsn[i]);
    }
    for (int i = n; i >= 1; i--) {
        suffix[i] = max(suffix[i + 1], wdfsn[i]);
    }
    int mxidx = 0;
    for (int i = 1; i <= n; i++) {
        if (max(prefix[dfsn[i]], suffix[outDfsn[i] + 1]) > wdfsn[dfsn[i]]) {
            if (mxidx == 0 || wdfsn[dfsn[i]] > wdfsn[dfsn[mxidx]]) {
                mxidx = i;
            }
        }
    }
    cout << mxidx << '\n';
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
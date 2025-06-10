#include <algorithm>
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
    vector<vector<i64>> graph(n);
    vector<int>         degree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++, degree[v]++;
    }
    vector<i64> que;
    int         curmx = 0;
    for (int i = 0; i < n; i++) {
        if (degree[i] > curmx) {
            curmx = degree[i];
            que.clear();
            que.push_back(i);
        } else if (degree[i] == curmx) {
            que.push_back(i);
        }
    }
    int ans = 1;
    if (que.size() <= 2) {

        int mx = max_element(degree.begin(), degree.end()) - degree.begin();
        ans += degree[mx] - 1;
        degree[mx] = 0;
        for (int adj : graph[mx]) {
            degree[adj]--;
        }
        int mx2 = max_element(degree.begin(), degree.end()) - degree.begin();
        ans += degree[mx2] - 1;
    } else if (que.size() > 2) {
        ans += curmx * 2 - 2;
    }
    cout << ans << '\n';
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
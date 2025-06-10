#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m >> s;
    Graph                          graph(n + 1);
    vector<vector<pair<int, int>>> query(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        query[x].emplace_back(y, i);
        query[y].emplace_back(x, i);
    }
    vector<int> ans(m + 1);
    vector<int> ufFather(n + 1);
    vector<int> beenVis(n + 1);

    auto ufFind = [&](auto&& self, int root) -> int {
        return root == ufFather[root] ? root : (ufFather[root] = self(self, ufFather[root]));
    };
    auto dfs = [&](auto&& self, int root) -> void {
        ufFather[root] = root;
        beenVis[root]  = true;
        for (int adj : graph[root]) {
            if (beenVis[adj]) continue;
            self(self, adj);
            ufFather[adj] = root;
        }
        for (pair<int, int> q : query[root]) {
            if (!beenVis[q.first]) continue;
            ans[q.second] = ufFind(ufFind, q.first);
        }
    };
    dfs(dfs, s);
    for (int i = 0; i < m; i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}
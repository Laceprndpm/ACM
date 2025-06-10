#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    map<pair<int, int>, int> vis;
    int                      n, s1, s2;
    cin >> n >> s1 >> s2;
    vector<vector<int>> graph1(n + 1), graph2(n + 1);
    int                 m1, m2;
    cin >> m1;
    for (int i = 0; i < m1; i++) {
        int u, v;
        cin >> u >> v;
        graph1[u].push_back(v);
        graph1[v].push_back(u);
    }
    cin >> m2;
    for (int i = 0; i < m2; i++) {
        int u, v;
        cin >> u >> v;
        graph2[u].push_back(v);
        graph2[v].push_back(u);
    }

    struct node {
        int dis, x, y;

        bool operator<(node t) const
        {
            return dis > t.dis;
        }
    };

    priority_queue<node> pq;
    pq.push({0, s1, s2});
    i64 ans = -1;
    while (!pq.empty() && ans == -1) {
        auto [dis, x, y] = pq.top();
        pq.pop();
        for (int u : graph1[x]) {
            for (int v : graph2[y]) {
                if (u - v == 0 && x == y) {
                    ans = dis;
                }
                if (vis[{u, v}]) continue;
                vis[{u, v}] = 1;
                pq.push({dis + abs(u - v), u, v});
            }
        }
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
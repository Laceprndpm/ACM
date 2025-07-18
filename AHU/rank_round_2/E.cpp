#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    // 考虑Floyd
    // 假如
    // A-B所有的边一开始都标记为T，即只可直达
    // 
    // 
    // 
    // 位置不变等价于什么？最短路不变
    // 我应该枚举每一个球，然后跑dijkstra，然后dij复杂度是多少？反正不超过O(m)
    // 如果两个球间的线大于他们间的最短路，那么是不是就可以删除？
    // 那么现在，我枚举每个球作为起点，然后就可以获得其他球的最短路，随后如果存在线
    // s-u>dist(s-u)，则可以考虑删除，如果所有考虑都认为可以删除，那么就可以删除
    // 不对
    // 要求出u->v时必须走的所有路
    // 假如u->v有两条路可以最短，那么可以删掉直达的路，其他路都最好别删
    //
    // 最小生成树？不，等边三角形
    //
    map<tuple<int, int, int>, int> idx;

    vector<vector<pair<int, int>>> g(n + 1);

    vector<int> ans;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u == v) {
            ans.push_back(i);
            continue;
        }
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        idx[{min(u, v), max(u, v), w}] = i;
    }
    auto cmp = [&](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b.first;
    };
    vector<int> vote(m + 1);
    auto        dijkstra = [&](int s) -> void {
        vector<int>                                                           dist(n + 1, INF);
        vector<int>                                                           vis(n + 1);
        vector<int>                                                           viscnt(n + 1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
        pq.push({0, s});
        dist[s] = 0;
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto [v, w] : g[u]) {
                if (dist[v] > w + d) {
                    dist[v] = w + d;
                    pq.push({w + d, v});
                    viscnt[v] = 1;
                } else if (dist[v] == w + d) {
                    viscnt[v]++;
                }
            }
        }
        for (auto [adj, w] : g[s]) {
            if (w > dist[adj] || viscnt[adj] >= 2) {
                vote[idx[{min(adj, s), max(adj, s), w}]]++;
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        dijkstra(i);
    }

    for (int i = 1; i <= m; i++) {
        if (vote[i] >= 2) {
            ans.push_back(i);
        }
    }
    sor(ans);
    cout << sz(ans) << '\n';
    for (int i : ans) {
        cout << i << ' ';
    }
    // 应该不存在绳子完全相同吧？因为它没说有多种答案
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
#include <deque>
#include <functional>
#include <iostream>
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

void solve()
{
    int n, s, t, kx, kl;
    cin >> n >> s >> t >> kx >> kl;
    vector<vector<int>> graph(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }
    vector<int> dist(n + 1, 0);
    vector<int> fa(n + 1);
    dist[1]                         = 1;
    int                      faridx = 1;
    vector<int>              vis(n + 1, false);
    function<void(int, int)> dfs = [&](int root, int last) {
        fa[root] = last;
        if (dist[root] > dist[faridx]) {
            faridx = root;
        }
        for (int adj : graph[root]) {
            if (adj == last || vis[adj]) continue;
            dist[adj] = dist[root] + 1;
            dfs(adj, root);
        }
    };
    auto bfs = [&](int s, int t) {
        deque<int> q;
        q.push_back(s);
        vector<int> vis(n + 1);
        vector<int> dist(n + 1, INF);
        dist[s] = 0;
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            if (vis[cur]) continue;
            vis[cur] = 1;
            for (int adj : graph[cur]) {
                if (dist[adj] > dist[cur] + 1) {
                    dist[adj] = dist[cur] + 1;
                    q.push_back(adj);
                }
            }
        }
        return dist[t];
    };
    dfs(1, 0);
    dist.resize(n + 1, 0);
    dist[faridx] = 0;
    dfs(faridx, 0);
    int B = faridx;
    int d = dist[B] + 1;
    if (2 * kx >= kl) {
        cout << "Alice\n";
        return;
    }
    if (bfs(s, t) <= kx) {
        cout << "Alice\n";
        return;
    }
    if (2 * kx + 1 >= d) {
        cout << "Alice\n";
        return;
    }
    cout << "Bob\n";
}
新建Microsoft Word 文档 (4).docx
signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 也许与直径有关
    // A的速度如果>2 * B那么一定成功
    // 如果A < 2 * B，则可以尝试通过地形。。。
    //
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    // int ans = INF;
    // fa[A]   = 0;
    // for (int i = B; i != 0; i = fa[i]) {
    //     dist[i] = 0;
    //     vis[i]  = true;
    // }
    // for (int i = B; i != 0; i = fa[i]) {
    //     dfs(i, fa[i]);
    // }
    // for (int i = 1; i <= n; i++) {
    //     ans = max(ans, dist[i]);
    // }
    // cout << ans;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
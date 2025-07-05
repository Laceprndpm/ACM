#include <deque>
#include <iostream>
#include <set>
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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    vector<vector<int>> trace(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        trace[v].push_back(u);
    }
    for (int i = 0; i < n - 1; i++) {
        graph[i].pb(i + 1);
        // trace[i + 1].pb(i);
    }
    vector<int> dist(n, INF);
    deque<int>  q;
    dist[0] = 0;
    q.push_back(0);
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        for (int v : graph[cur]) {
            if (dist[v] == INF) {
                dist[v] = dist[cur] + 1;
                q.push_back(v);
            }
        }
    }
    multiset<int>       max_right;
    vector<int>         ans(n);
    vector<vector<int>> ttl(n);
    // dist[v] >= v - s
    // v - dist[v] <= s

    for (int s = n - 1; s >= 0; s--) {
        for (int j : ttl[s]) {
            max_right.erase(max_right.find(j));
        }
        int curMaxRight = max_right.empty() ? -1 : *prev(max_right.end());
        ans[s]          = s >= curMaxRight ? 1 : 0;
        for (int p : trace[s]) {
            max_right.insert(s - dist[p] - 1);
            ttl[p].pb(s - dist[p] - 1);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
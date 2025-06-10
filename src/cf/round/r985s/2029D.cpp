#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <queue>
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

constexpr int         INF = 1e9;
vector<array<int, 3>> ans;

void enter(void)
{
    cout << sz(ans) << '\n';
    for (auto i : ans) {
        for (int j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
    ans.clear();
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<set<int>> g(n + 1);
    vector<int>      deg(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
        deg[u]++, deg[v]++;
    }
    // auto cmp = [&](const int u, const int v) -> bool {
    //     return deg[u] > deg[v];
    // };
    // priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    deque<int> que;
    for (int i = 1; i <= n; i++) {
        if (deg[i] > 1) {
            que.push_back(i);
        }
    }
    auto change_vertices = [&](int u, int v) {
        if (g[u].count(v)) {
            g[u].extract(v);
            g[v].extract(u);
            deg[u]--;
            deg[v]--;
        } else {
            g[u].insert(v);
            g[v].insert(u);
            deg[u]++;
            deg[v]++;
        }
    };
    auto op = [&](int u, int v, int w) {
        array<int, 3> tp = {u, v, w};
        for (int i = 0; i < 3; i++) {
            change_vertices(tp[i], tp[(i + 1) % 3]);
        }
        ans.push_back(tp);
    };
    while (!que.empty()) {
        int cur = que.front();
        que.pop_front();
        if (deg[cur] <= 1) {
            continue;
        }
        int                   last1 = -1;
        vector<array<int, 3>> todo;
        for (int adj : g[cur]) {
            if (last1 == -1) {
                last1 = adj;
            } else {
                // change_vertices(last1, adj);
                // change_vertices(last1, cur);
                // change_vertices(cur, adj);
                todo.push_back({cur, last1, adj});
                last1 = -1;
            }
        }
        for (auto i : todo) {
            auto [cur, last1, adj] = i;
            op(cur, last1, adj);
            if (deg[adj] > 1) que.push_back(adj);
            if (deg[last1] > 1) que.push_back(last1);
        }
    }
    bool ok = true;
    int  u, v;
    for (int i = 1; i <= n; i++) {
        if (deg[i] != 0) {
            ok = false;
            assert(g[i].size());
            u = i, v = *g[u].begin();
            break;
        }
    }
    if (ok) {
        enter();
        return;
    }
    vector<int> vis(n + 1);
    vis[u] = 1, vis[v] = 1;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        for (int adj : g[i]) {
            vis[adj] = 1;
        }
        vis[i] = 1;
        op(u, v, i);
        v = i;
    }
    enter();
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
    //
    // let's start with the case which only has 3 vertices
    // one edge, need one op
    // there edge need one op
    // what is unchanged?
    // edges will - 1 + 2, + 3 -2 + 1 -3
    // must be odds, but is that useful?
    // if I already has a tree
    // when add an other vetrices, I should delete other edge and leave ONLY one, by choose a1, a2, b1? No, will distrup
    // choose twice? No way
    // add to a vec?
    // if a graph is made into a forest
    //
    // FAILED
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
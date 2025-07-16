#include <array>
#include <deque>
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
    int n, k;
    cin >> n >> k;
    vector<vector<vector<int>>> graph(n, vector<vector<int>>(k));
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        for (int j = 0; j < k; j++) {
            graph[u][j].eb(v);
            graph[v][j].eb(u);
        }
        // graph[u].eb(v, i);
        // graph[v].eb(u, i + n - 1);
    }
    vector<int>          dis(n, INF);
    deque<array<int, 4>> dq;  // 位置，fa，cur
    dq.pb({0, 0, 0, 0});
    while (!dq.empty()) {
        auto [u, fa, cur, cur_dist] = dq.front();
        dq.pop_front();
        if (cur != k) {
            int hasfa = 0;
            for (int v : graph[u][cur]) {
                if (v == fa) {
                    hasfa = 1;
                    continue;
                }
                dq.pb({v, u, cur + 1, cur_dist});
            }
            if (hasfa) {
                graph[u][cur] = {fa};
            } else {
                graph[u][cur] = {};
            }
        } else {
            dis[u] = min(dis[u], cur_dist);
            for (int v : graph[u][0]) {
                dq.pb({v, u, 1, cur_dist + 1});
            }
            graph[u][0] = {};
        }
    }
    for (int i = 1; i < n; i++) {
        cout << (dis[i] == INF ? -1 : dis[i] + 1) << ' ';
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
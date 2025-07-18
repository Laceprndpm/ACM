#include <algorithm>
#include <iostream>
#include <map>
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
    map<tuple<int, int, int>, int> idx;

    vector<vector<int>> g(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> is_stable(n + 1, vector<int>(n + 1, 0));
    vector<int>         ans;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        int mn = min(u, v), mx = max(u, v);
        u = mn, v = mx;
        if (u == v) {
            ans.push_back(i);
            continue;
        }
        if (g[u][v] > w && g[u][v] != INF) {
            ans.push_back(idx[{u, v, g[u][v]}]);
        } else if (g[u][v] <= w) {
            ans.push_back(i);
            continue;
        }
        g[u][v]         = w;
        g[v][u]         = w;
        idx[{u, v, w}]  = i;
        is_stable[u][v] = 1;
        is_stable[v][u] = 1;
    }
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                if (i == k || k == j || i == j) continue;
                if (g[i][k] >= g[i][j] + g[j][k]) {
                    if (g[i][k] != INF && is_stable[i][k]) {
                        ans.push_back(idx[{i, k, g[i][k]}]);
                        is_stable[i][k] = 0;
                        is_stable[k][i] = 0;
                    }
                    g[i][k] = g[i][j] + g[j][k];
                }
            }
        }
    }
    sor(ans);
    cout << sz(ans) << '\n';
    for (int i : ans) {
        cout << i << ' ';
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
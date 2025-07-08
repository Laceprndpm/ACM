#include <algorithm>
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
    vector<vector<i64>> graph(n);
    vector<i64>         deg(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        graph[x].eb(y);
        deg[y]++;
    }
    vector<i64> que;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            que.eb(i);
        }
    }
    vector<i64> maxlen(n, -1);
    auto        dfs = [&](auto&& dfs, i64 u) -> i64 {
        if (maxlen[u] != -1) {
            return maxlen[u];
        }
        i64 maxson = 0;
        for (i64 v : graph[u]) {
            maxson = max(maxson, dfs(dfs, v));
        }
        return maxlen[u] = maxson + 1;
    };
    i64 ans = -1;
    for (i64 i : que) {
        ans = max(dfs(dfs, i), ans);
    }
    cout << ans - 1 << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
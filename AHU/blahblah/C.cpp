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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].eb(v);
        graph[v].eb(u);
    }
    enum class Color {
        white   = 0,
        black   = 1,
        unknown = 2,
    };
    vector<Color> color(n, Color::unknown);
    auto          dfs = [&](this auto&& dfs, int cur, Color c) -> int {
        int ok     = 1;
        color[cur] = c;
        for (int v : graph[cur]) {
            if (color[v] == c) {
                ok = 0;
            }
        }
        if (ok) {
            for (int v : graph[cur]) {
                ok &= dfs(v, static_cast<Color>((!static_cast<int>(c))));
            }
        }
        return ok;
    };
    if (dfs(0, Color::white)) {
        cout << "Bob\n";
    }
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
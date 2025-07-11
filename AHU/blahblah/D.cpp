#include <deque>
#include <iostream>
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
    vector<vector<pair<int, int>>> go(n);
    vector<vector<pair<int, int>>> from(n);
    for (int i = 0; i < m; i++) {
        int  u, v;
        char c;
        cin >> u >> v >> c;
        u--, v--;
        go[u].eb(v, c);
        from[v].eb(u, c);
    }
    vector<vector<int>>   ok(n, vector<int>(n));
    deque<pair<int, int>> que;
    for (int u = 0; u < n; u++) {
        for (auto [v, c] : go[u]) {
            que.eb(u, v);
            for (auto [vv, c2] : go[v]) {
                if (c2 != c) continue;
                que.eb(u, vv);
            }
        }
    }
    while (!que.empty()) {
        auto [u, v] = que.front();
        que.pop_front();
        if (ok[u][v]) continue;
        ok[u][v] = 1;
        for (auto [uu, c1] : from[u]) {
            for (auto [vv, c2] : go[v]) {
                if (c1 == c2) {
                    que.eb(uu, vv);
                }
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            ans += ok[i][j];
        }
    }
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
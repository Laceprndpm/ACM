#include <algorithm>
#include <iostream>
#include <map>
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
    int n;
    int m;
    cin >> n >> m;
    vector<pair<int, int>> edge;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) {
            swap(u, v);
        }
        edge.push_back({u, v});
    }
    vector<pair<int, int>> pop;
    pop.reserve(n * (n - 1) / 2);
    int ans     = INF;
    int perpare = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pop.push_back({i, j});
            if (find(all(edge), pop.back()) != edge.end()) {
                perpare |= 1 << ((int)pop.size() - 1);
            }
        }
    }
    for (int i = 0; i < (1 << (n * (n - 1) / 2)); i++) {
        int ok = 1;
        if (ans < __builtin_popcount(i)) {
            continue;
        }
        int deg[8] = {0};

        int cur = i ^ perpare;
        if (__builtin_popcount(cur) != n) {
            continue;
        }
        for (int j = 0; j < n * (n - 1) / 2; j++) {
            if (cur >> j & 1) {
                auto [u, v] = pop[j];
                deg[u]++, deg[v]++;
            }
        }

        for (int j = 0; ok && j < n; j++) {
            if (deg[j] != 2) {
                ok = 0;
            }
        }
        if (ok) {
            ans = min(ans, __builtin_popcount(i));
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
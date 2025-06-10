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

int cnt = 2;

void solve()
{
    cnt = 2;
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int>         deg(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    int s;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            s = i;
            break;
        }
    }
    vector<int> arr(n + 1);
    auto        dfs = [&](auto self, int u) -> void {
        for (int adj : g[u]) {
            if (arr[adj] == 0) {
                if (cnt - arr[u] != 1 && (cnt - arr[u]) % 2 == 1) {
                    cnt++;
                }
                if (cnt - arr[u] == 2) {
                    cnt += 2;
                }
                arr[adj] = cnt++;
                self(self, adj);
            }
        }
        return;
    };
    arr[s] = 1;
    dfs(dfs, s);
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << ' ';
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
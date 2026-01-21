#include <iostream>
#include <vector>
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int>         siz(n + 1);
    vector<vector<int>> adj(n + 1);
    auto                dfs0 = [&](auto&& self, int u, int fa) -> void {
        siz[u] = 1;
        for (int v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
            siz[u] += siz[v];
        }
    };
    ll ans = 0;
    ll tmp = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs0(dfs0, 0, 0);
    for (int v : adj[0]) {
        ans += tmp * siz[v];
        ans += siz[v];
        tmp += siz[v];
    }
    auto check = [&](auto&& self, int u, int fa) -> bool {
        if (u == 1) return true;
        for (int v : adj[u]) {
            if (v == fa) continue;
            if (self(self, v, u)) return true;
        }
        return false;
    };
    for (int v : adj[0]) {
        if (check(check, v, 0)) {
            adj[v].pb(n);
            adj[n].pb(v);
            adj[0].pb(n);
            adj[n].pb(0);
            adj[0].erase(find(all(adj[0]), v));
            adj[v].erase(find(all(adj[v]), 0));
            break;
        }
    }
    vector<int> indfs(n + 1), outdfs(n + 1);
    int         ptr = 0;
    auto        dfs = [&](auto&& self, int u, int fa) -> void {
        indfs[u] = ++ptr;
        siz[u]   = 1;
        for (int v : adj[u]) {
            if (v == fa) continue;
            self(self, v, u);
            siz[u] += siz[v];
        }
        outdfs[u] = ptr;
    };
    dfs(dfs, n, -1);
    auto is_an = [&](int u, int v) { return indfs[u] <= indfs[v] && outdfs[u] >= indfs[v]; };
    int  lft = 0, rgt = 1;
    for (int i = 1; i < n; i++) {
        int u = i;
        // 如果u是lft或rgt祖先
        if (is_an(u, lft) || is_an(u, rgt)) {
            ;
        } else if (is_an(lft, u)) {
            lft = u;
        } else if (is_an(rgt, u)) {
            rgt = u;
        } else {
            break;
        }
        ans += 1ll * siz[rgt] * siz[lft];
    }
    cout << ans + 1 << '\n';
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
    int t = 1;
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
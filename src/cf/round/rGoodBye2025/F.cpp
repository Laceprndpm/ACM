#include <iostream>
#include <random>
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
constexpr ll  P   = 998244353;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    vector<int>         siz(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vector<ll> trees;
    auto       dfs = [&](auto&& self, int u, int fa) -> int {
        siz[u]   = 1;
        int sons = 1;
        for (int v : adj[u]) {
            if (v == fa) continue;
            sons += self(self, v, u);
            siz[u] += siz[v];
        }
        if (siz[u] % 2 == 0 || u == 1) {
            trees.pb(sons);
            return 0;
        }
        return sons;
    };
    dfs(dfs, 1, 0);
    ll rtsz = trees.back();
    trees.pop_back();
    ll         m = trees.size();
    vector<ll> prefix(1, 1);
    vector<ll> suffix(m + 1, 1);
    for (int i = 0; i < m; i++) {
        prefix.pb(1ll * prefix.back() * trees[i] % P);
    }
    for (int i = m - 1; i > 0; i--) {
        suffix[i] = suffix[i + 1] * trees[i] % P;
    }
    ll         ans = 0;
    ll         tmp = 1;
    vector<ll> fac(m + 1);
    fac[0] = 1;
    for (int i = 1; i <= m; i++) {
        fac[i] = fac[i - 1] * i % P;
    }
    for (int i = 0; i < m; i++) {
        ans += (((((prefix[i] * suffix[i + 1] % P) * (prefix[i] * suffix[i + 1] % P)) % P * trees[i]) % P) * fac[m - 1])
               % P;
        ans %= P;
    }
    ans = ans * rtsz % P;
    if (ans == 0) ans = 1;
    cout << ans << '\n';
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
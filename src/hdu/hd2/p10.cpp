#include <functional>
#include <iostream>
#include <vector>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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
#define len(x)  int(x.size())
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

void dfs1(int o) {}

void dfs2(int o, int t) {}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<vector<int>> graph(n + 1);
    vector<int>         son;
    vector<int>         siz;
    vector<int>         dep;
    vector<int>         nxt;
    vector<int>         h;
    vector<int>         fa;
    vector<int>         p;
    vector<int>         top;
    vector<int>         dfn;
    vector<int>         rnk;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].eb(v);
        graph[v].eb(u);
    }
    function<void(int)> dfs1 = [&](int o) -> void {
        son[o] = -1;
        siz[o] = 1;
        for (int j = h[o]; j; j = nxt[j])
            if (!dep[p[j]]) {
                dep[p[j]] = dep[o] + 1;
                fa[p[j]]  = o;
                dfs1(p[j]);
                siz[o] += siz[p[j]];
                if (son[o] == -1 || siz[p[j]] > siz[son[o]]) son[o] = p[j];
            }
    };
    function<void(int, int)> dfs2 = [&](int o, int t) -> void {
        top[o] = t;
        cnt++;
        dfn[o]   = cnt;
        rnk[cnt] = o;
        if (son[o] == -1) return;
        dfs2(son[o], t);  // 优先对重儿子进行 DFS，可以保证同一条重链上的点 DFS 序连续
        for (int j = h[o]; j; j = nxt[j])
            if (p[j] != son[o] && p[j] != fa[o]) dfs2(p[j], p[j]);
    };
    for (int i = 0; i < m; i++) {
        int opt;
        cin >> opt;
        if (opt == 1) {

        } else {
        }
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
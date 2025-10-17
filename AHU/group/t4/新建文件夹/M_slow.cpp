#include <array>
#include <cassert>
#include <iostream>
#include <numeric>
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
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)

struct DSU {
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) { init(n); }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x) { return siz[find(x)]; }
};

constexpr int P = 998244353;

constexpr u64 power(u64 a, u64 b)
{
    u64 res = 1;
    for (; b != 0; b /= 2, a = a * a % P) {
        if (b & 1) {
            res = (res * a) % P;
        }
    }
    return res;
}

constexpr int optnum   = 2e7;
vector<int>   cacheopt = [](int _init = optnum) -> vector<int> {
    vector<int> vec(optnum);
    vec[1] = 1;
    for (int i = 2; i < optnum; i++) {
        vec[i] = ((u64)(P - P / i) * vec[P % i]) % P;
    }
    return vec;
}();

constexpr u64 inv(u64 x)
{
    if (x < optnum) {
        return cacheopt[x];
    } else {
        return power(x, P - 2);
    }
}

void solve()
{
    int n;
    cin >> n;
    if (n == 1) {
        cout << '\n';
        return;
    }
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<vector<int>> newgraph(n + 1, vector<int>());
    vector<int>         vis(n + 1);
    DSU                 dsu(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    vector<array<u32, 2>> dp(n + 1);
    for (int i = 1; i <= n - 1; i++) {
        int u;
        cin >> u;
        vis[u] = 1;
        for (int adj : graph[u]) {
            if (!vis[adj]) {
                newgraph[u].pb(adj);
                newgraph[adj].pb(u);
            } else {
                dsu.merge(u, adj);
            }
        }
        int  cnt = 0;
        auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
            if (!vis[u]) {
                cnt++;
                dp[u][1] = 1;
                dp[u][0] = 0;
                return;
            }
            u64 dpcnt0 = 1;
            u64 dpcnt1 = 0;
            for (int v : newgraph[u]) {
                if (v == fa) continue;
                dfs(v, u);
                dpcnt0 = dpcnt0 * (dp[v][0] + dp[v][1]) % P;
            }
            for (int v : newgraph[u]) {
                if (v == fa) continue;
                dpcnt1 = (dpcnt1 + dpcnt0 * inv(dp[v][0] + dp[v][1]) % P * dp[v][1]) % P;
            }
            dp[u][0] = dpcnt0, dp[u][1] = dpcnt1;
        };
        u64 ans = 1;
        for (int i = 1; i <= n; i++) {
            if (dsu.find(i) == i && vis[i]) {
                cnt--;
                dfs(i, -1);
                ans = ans * dp[i][1] % P;
            }
        }
        cout << ans * power(2, cnt) % P << '\n';
    }
}

signed main()
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
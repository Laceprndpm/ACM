#include <iostream>
#include <map>
#include <utility>
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
#define mp      make_pair
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
    int n, q;
    cin >> n >> q;
    vector<int> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    vector<vector<pair<i64, i64>>> graph(n + 1);
    for (int i = 0; i < n - 1; i++) {
        i64 u, v, c;
        cin >> u >> v >> c;
        graph[u].eb(v, c);
        graph[v].eb(u, c);
    }
    vector<int>           fater(n + 1);
    vector<i64>           fa_c(n + 1);
    vector<map<i64, i64>> sonval(n + 1);
    i64                   ans = 0;

    auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
        for (auto [v, c] : graph[u]) {
            if (v == fa) continue;
            fater[v] = u;
            fa_c[v]  = c;
            sonval[u][ai[v]] += c;
            if (ai[v] != ai[u]) ans += c;
            dfs(v, u);
        }
    };
    dfs(1, 0);
    for (int i = 0; i < q; i++) {
        int u, x;
        cin >> u >> x;
        int fa = fater[u];
        if (fa) {
            sonval[fa][ai[u]] -= fa_c[u];
            sonval[fa][x] += fa_c[u];
            if (ai[fa] == ai[u]) {
                ans += fa_c[u];
            }
            if (ai[fa] == x) {
                ans -= fa_c[u];
            }
        }
        if (sonval[u].count(ai[u])) {
            ans += sonval[u][ai[u]];
        }
        if (sonval[u].count(x)) {
            ans -= sonval[u][x];
        }
        ai[u] = x;
        cout << ans << '\n';
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
    // 如果直接暴力会怎么样？每次修改的点的相连的所有边都会被更新
    // 是不是可以只维护颜色相同的颜色集？
    // 假如每个点维护一个map<int, pair<set, int>>> 分别为点集，与该点集
    // 那我还得遍历他的同色邻居
    // 如果只是对该点打标记
    // 假如这个点有若干儿子
    // 那么我每次更新点
    // 1.检查父亲颜色，不需要检查儿子，因为儿子会上传
    // 2.上传给父亲，告诉父亲，他这个颜色的边权该-=c了
    // 3.更新答案
    // 4.给自己颜色
    //
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
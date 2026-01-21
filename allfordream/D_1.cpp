#include <iostream>
#include <utility>
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
    // x, 则前面不能存在x - 1
    // dp0[x]表示没有x时的最少删除元素
    // 若当前删去了x，则只保留dp0[x - 1]和dp0[x]
    //
    // 如果考虑每个元素的最早出现位置
    // 一棵权值线段树
    // dp[x]是一棵线段树，表示最早出现在i处至少删多少个元素
    // dp[x-1]则 = dp[x]
    //
    int n;
    cin >> n;
    vector<vector<int>> pos(n + 1);

    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        pos[val].pb(i);
    }
    vector<pair<int, int>> dp, ndp;
    dp.pb({INF, 0});
    for (int i = n; i >= 1; i--) {
        int cnt = pos[i].size();
        int mx  = 0;
        for (auto [x, y] : dp) {
            mx = max(mx, y);
        }
        ndp     = {{INF, mx}};
        int j   = 0;
        int ptr = 0;
        int cur = 0;
        for (; j < cnt; j++) {
            int cpos = pos[i][j];
            while (ptr + 1 < dp.size() && dp[ptr + 1].fi < cpos) {
                ptr++;
            }
            cur = max(cur, dp[ptr].se - j);
            ndp.pb({cpos, max(j + 1 + cur, mx)});
        }
        dp = std::move(ndp);
    }
    int mx = 0;
    for (auto [x, y] : dp) {
        mx = max(mx, y);
    }
    cout << n - mx << '\n';
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
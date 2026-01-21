#include <algorithm>
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
#pragma GCC   optimize(3)
#pragma GCC   target("avx")
#pragma GCC   optimize("Ofast")
#pragma GCC   optimize("inline")
#pragma GCC   optimize("-fgcse")
#pragma GCC   optimize("-fgcse-lm")
#pragma GCC   optimize("-fipa-sra")
#pragma GCC   optimize("-ftree-pre")
#pragma GCC   optimize("-ftree-vrp")
#pragma GCC   optimize("-fpeephole2")
#pragma GCC   optimize("-ffast-math")
#pragma GCC   optimize("-fsched-spec")
#pragma GCC   optimize("unroll-loops")
#pragma GCC   optimize("-falign-jumps")
#pragma GCC   optimize("-falign-loops")
#pragma GCC   optimize("-falign-labels")
#pragma GCC   optimize("-fdevirtualize")
#pragma GCC   optimize("-fcaller-saves")
#pragma GCC   optimize("-fcrossjumping")
#pragma GCC   optimize("-fthread-jumps")
#pragma GCC   optimize("-funroll-loops")
#pragma GCC   optimize("-fwhole-program")
#pragma GCC   optimize("-freorder-blocks")
#pragma GCC   optimize("-fschedule-insns")
#pragma GCC   optimize("inline-functions")
#pragma GCC   optimize("-ftree-tail-merge")
#pragma GCC   optimize("-fschedule-insns2")
#pragma GCC   optimize("-fstrict-aliasing")
#pragma GCC   optimize("-fstrict-overflow")
#pragma GCC   optimize("-falign-functions")
#pragma GCC   optimize("-fcse-skip-blocks")
#pragma GCC   optimize("-fcse-follow-jumps")
#pragma GCC   optimize("-fsched-interblock")
#pragma GCC   optimize("-fpartial-inlining")
#pragma GCC   optimize("no-stack-protector")
#pragma GCC   optimize("-freorder-functions")
#pragma GCC   optimize("-findirect-inlining")
#pragma GCC   optimize("-fhoist-adjacent-loads")
#pragma GCC   optimize("-frerun-cse-after-loop")
#pragma GCC   optimize("inline-small-functions")
#pragma GCC   optimize("-finline-small-functions")
#pragma GCC   optimize("-ftree-switch-conversion")
#pragma GCC   optimize("-foptimize-sibling-calls")
#pragma GCC   optimize("-fexpensive-optimizations")
#pragma GCC   optimize("-funsafe-loop-optimizations")
#pragma GCC   optimize("inline-functions-called-once")
#pragma GCC   optimize("-fdelete-null-pointer-checks")
#pragma GCC   optimize(2)

void solve()
{
    // a符合，2a,3a..才有可能符合
    // 只需要所有质数以及其次方 < 2sqrt(n)
    int n, m;
    cin >> n >> m;
    vector<string> grid(n + 2);

    int tcnt = 0;
    for (int i = 1; i <= n; i++) {
        cin >> grid[i];
        grid[i] = '0' + grid[i] + '0';
        tcnt += count(all(grid[i]), '1');
    }
    grid[0] = grid[n + 1] = string(m + 2, '0');
    int  bound            = min(n, m);
    auto check            = [&](const vector<string>& grid) {
        int                 total = 0;
        vector<vector<int>> vis(n + 1, vector<int>(m + 1, 0));
        int                 cnt = 0;
        auto                dfs = [&](this auto&& self, int x, int y) {
            if (grid[x][y] != '1' || vis[x][y]) return;
            vis[x][y] = 1, cnt++;
            for (auto [dx, dy] : vector<pair<int, int>>{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}) {
                self(dx + x, dy + y);
            }
        };
        for (int i = 1; i <= n; i++) {
            total += count(all(grid[i]), '1');
            for (int j = 1; j <= m && !cnt; j++) {
                dfs(i, j);
            }
        }
        return total && total == cnt;
    };
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + (grid[i][j] == '1');
        }
    }
    auto check_val = [&](int x) {
        vector<vector<int>> c(n + 2, vector<int>(m + 2));
        vector<string>      gr(n + 2, string(m + 2, '0'));
        for (int i = x; i <= n; i++) {
            for (int j = x; j <= m; j++) {
                if (prefix[i][j] - prefix[i - x][j] - prefix[i][j - x] + prefix[i - x][j - x] == x * x) {
                    c[i - x + 1][j - x + 1] += 1;
                    c[i + 1][j - x + 1] -= 1;
                    c[i - x + 1][j + 1] -= 1;
                    c[i + 1][j + 1] += 1;
                    gr[i - x + 1][j - x + 1] = '1';
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                c[i][j] += c[i][j - 1];
            }
        }
        int cnt = 0;
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                c[i][j] += c[i - 1][j];
                if (c[i][j]) cnt++;
            }
        }
        return cnt == tcnt && check(gr);
    };
    int l = 1, r = bound;
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check_val(mid)) {
            ans = mid;
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
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
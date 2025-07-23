#include <array>
#include <cassert>
#include <iostream>
#include <queue>
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

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<i64>> ai(n + 1, vector<i64>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> ai[i][j];
        }
    }
    vector<vector<i64>> dp(n + 1);  // [0, i] 的最优情况
    dp[0] = {0};
    for (int i = 1; i <= n; i++) {
        priority_queue<array<i64, 3>> pq;

        for (int j = i - 2; j >= -1; j--) {  // 枚举上一个状态，并且要落笔
            pq.push({(j < 0 ? 0 : dp[j][0]) + ai[j + 2][i], j, 0});
        }

        pq.push({dp[i - 1][0], i - 1, 0});  // 直接转移，不落笔

        while (!pq.empty() && dp[i].size() < k) {
            auto [val, dpIdx, idx] = pq.top();
            pq.pop();

            dp[i].push_back(val);

            if (dpIdx < 0 || idx + 1 >= dp[dpIdx].size()) continue;

            i64 valNext;
            if (dpIdx == i - 1) {
                valNext = dp[dpIdx][idx + 1];
            } else {
                valNext = ai[dpIdx + 2][i] + dp[dpIdx][idx + 1];
            }
            pq.push({valNext, dpIdx, idx + 1});
        }
    }
    for (int ans : dp[n]) {
        cout << ans << ' ';
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
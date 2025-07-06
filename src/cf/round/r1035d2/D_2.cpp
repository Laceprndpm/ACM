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

void solve()
{
    i64 n, MOD;
    cin >> n >> MOD;
    vector<i64> dp(n + 1);
    dp[0] = 1;                                                                    // dp[i]移出了i个数的方案数
    for (i64 i = n; i >= 1; i--) {                                                // 考虑i号位置
        for (i64 j = n - i; j >= 0; j--) {                                        // 目前被移出了j个
            dp[j + 1] = (dp[j + 1] + dp[j] * (n - i - j + 1ll) % MOD * i) % MOD;  // a_idx, idx = [i, n]都可以，同时-j
            // dp[j] * 1 -> i
        }
    }
    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = (ans + dp[i]) % MOD;
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
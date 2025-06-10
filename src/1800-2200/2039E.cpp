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
constexpr int MOD = 998244353;

int solve()
{
    int n;
    cin >> n;
    i64         sum = 0;
    vector<i64> dp(n + 1);
    for (int i = n; i >= 1; i--) {
        dp[i] = ((1LL * i * sum + 1LL) % MOD);
        sum += dp[i];
        sum %= MOD;
    }
    i64 ans = n - 1;
    for (int k = 3; k <= n; k++) {
        i64 ways = (1LL * k * (k - 3) / 2) % MOD;
        ans += ways * dp[k];
        ans %= MOD;
    }
    cout << ans << '\n';
    return 0;
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
    //
    // 似乎只能有过去逆序对到新的逆序对
    // 除了第一步
    // 新加的数一定大于等于目前最大值
    // 是否每一步都可以选择推进多少逆序对，或者直接选择保持？
    // 对步骤1进行分讨后，
    // O(n) / O(NlogN)
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
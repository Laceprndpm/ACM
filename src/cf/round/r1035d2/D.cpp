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
    // 每个点枚举ai
    // 考虑 移出/不移出
    // 如果移出，方案数为前文总方案数*1
    // 如果不移出，则考虑是0,还是移出前面的
    // 0：前文方案数*1
    // 移出前面的：前面的没移出的方案累加
    //
    // 及时更新，所有数组中，该点还没有被移出的方案数
    //
    i64 n, MOD;
    cin >> n >> MOD;
    vector<i64> dp(n + 1);  // 该点还没移出的方案数
    vector<i64> dp2(n + 1);
    i64         qianwen = 1;
    i64         houwen  = 0;
    // 假如我枚举每次可以取哪个数，并且计算符合这个取法的数组个数
    // 1 2
    // 0 1
    // 1 0
    //
    for (i64 i = 1; i <= n; i++) {
        i64 suffix = 0;
        dp2[i]     = qianwen;  // 0
        vector<i64> chafen(n + 1);
        for (int j = i - 1; j >= 1; j--) {  // 该点取j
            // 对于[j, i)，可能被取，也可能不被，+ (suffix - dp) * dp
            //[1, j)则没有可能，则+dp*1
            // 所以每个点dp2[k] = dp * (i - k) + k

            suffix    = (suffix + dp[j]) % MOD;
            chafen[j] = suffix;
            dp2[i]    = (dp2[i] + suffix) % MOD;
        }
        houwen  = i * qianwen % MOD;  // 选择自己
        houwen  = (dp2[i] + houwen) % MOD;
        auto cp = chafen;
        for (int j = 0; j < n; j++) {
            chafen[j + 1] = (chafen[j] + chafen[j + 1]) % MOD;
        }
        for (int j = n - 1; j >= 0; j--) {
            cp[j] = (cp[j + 1] + cp[j]) % MOD;
        }
        for (i64 j = i - 1; j >= 1; j--) {
            dp2[j] = dp[j] * (chafen[j] - j * dp[j] % MOD + MOD) % MOD;  // 来自不为i时，选择其他数
            dp2[j] = (dp2[j] + dp[j] * cp[j] % MOD) % MOD;               // 不为i时，其他数
            dp2[j] = (dp[j] + i * dp2[j]) % MOD;
        }
        swap(dp, dp2);
        swap(qianwen, houwen);
    }
    cout << qianwen << '\n';
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
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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // C(n, k)
    // (4,4) + (4, 3) * (3 / 4) + (4, 2) / 2 + (4, 1) / 4
    //  1 +
    // 11
    // 对于有n个物品的集合
    // 假如j类物品有k个
    // 有k个的概率怎么
    // 此时通过A获胜的概率为(k / n) * (k / n)
    // n - k就是 n - k m - 1的情况
    // 也就是说，相同的有m个，好像没区别。。。
    // 假如
    // 1 2 3 4编号
    // 对于通过1获胜的情况
    // 目前有
    //
    int n, m;
    cin >> n >> m;
    vector<vector<double>> dp(n + 1, vector<double>(m + 1));

    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            for (int k = 0; k <= i; k++) {
                dp[i][j] += (dp[i - k][j - 1] * (double)(i - k) / i + ((double)k / i) * ((double)k / i));
            }
            dp[i][j] /= j;
        }
    }
    cout << dp[n][m] / m << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
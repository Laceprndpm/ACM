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
constexpr int M   = 5e5;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // dp[i]为有i种染色方式时，至少要多少顶点
    // dp[s] = dp[a] + dp[b] | s = (a + 2)(b + 2)
    //
    //
    vector<i64> dp(M + 50, INF);
    dp[1] = 1;
    for (i64 j = 1; j <= M; j++) {
        for (int i = 1; (i + 2) * j <= M; i++) {
            dp[(i + 2) * j] = min(dp[(i + 2) * j], dp[i] + dp[j]);
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (dp[n] == INF) {
            cout << -1 << '\n';
        } else {
            cout << dp[n] << '\n';
        }
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
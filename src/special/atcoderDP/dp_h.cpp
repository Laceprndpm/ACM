#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using u64         = unsigned long long;
using u32         = unsigned;
using u128        = unsigned __int128;
constexpr i64 MOD = 1e9 + 7;
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
    i64 h, w;
    cin >> h >> w;
    vector<string> bd(h);
    for (int i = 0; i < h; i++) {
        cin >> bd[i];
    }
    vector<vector<i64>> dp(h, vector<i64>(w));
    dp[0][0] = 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (bd[i][j] == '#') continue;
            if (i != 0) {
                dp[i][j] += dp[i - 1][j];
            }
            if (j != 0) {
                dp[i][j] += dp[i][j - 1];
            }
            dp[i][j] %= MOD;
        }
    }
    cout << dp[h - 1][w - 1];
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
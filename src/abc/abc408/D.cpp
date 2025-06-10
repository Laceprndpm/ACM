#include <algorithm>
#include <array>
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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<array<int, 3>> dp(n + 1, {INF, INF, INF});
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    for (int i = 0; i < n; i++) {
        dp[i + 1][0] = dp[i][0] + (s[i] == '1');
        dp[i + 1][1] = min(dp[i][0], dp[i][1]) + (s[i] == '0');
        dp[i + 1][2] = min(dp[i][2], dp[i][1]) + (s[i] == '1');
    }
    cout << min({dp[n][0], dp[n][1], dp[n][2]}) << '\n';
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
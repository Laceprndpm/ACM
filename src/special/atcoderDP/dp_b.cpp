#include <algorithm>
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
    int n, k;
    cin >> n >> k;
    vector<i64> hi(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> hi[i];
    }
    vector<i64> dp(n + 1, INF);
    dp[1] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= min(i + k, n); j++) {
            dp[j] = min(dp[j], dp[i] + abs(hi[i] - hi[j]));
        }
    }
    cout << dp[n] << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
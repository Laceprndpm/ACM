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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n), brr(m);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int j = 0; j < m; j++) {
        cin >> brr[j];
    }
    // vector<int> dp(n * m + 50);  // 当成本为n * m时，最多到哪？
    vector<i64> prefix(n + 1);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m, INF));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (brr[j] < arr[i]) break;
            if (j) dp[i][j] = min(dp[i][j - 1], dp[i][j]);
            i64 cur = brr[j] + prefix[i];
            int idx = upper_bound(all(prefix), cur) - bg(prefix) - 1;
            if (idx > n) idx = n;
            dp[idx][j] = min(dp[idx][j], dp[i][j] + m - j - 1);
        }
    }
    int ans = *min_element(all(dp[n]));
    if (ans >= INF) ans = -1;
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
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

constexpr i64 INF = 1e18;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n;
    cin >> n;
    vector<i64> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    vector<vector<int>> vis(n, vector<int>(n));
    vector<vector<i64>> dp(n, vector<i64>(n));
    auto                dfs = [&](auto&& dfs, int l, int r) -> i64 {
        if (l > r) return 0;
        if (vis[l][r]) return dp[l][r];
        vis[l][r]       = 1;
        return dp[l][r] = max(val[l] - dfs(dfs, l + 1, r), val[r] - dfs(dfs, l, r - 1));
    };
    cout << dfs(dfs, 0, n - 1);
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
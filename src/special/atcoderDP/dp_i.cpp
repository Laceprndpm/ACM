#include <array>
#include <cstdio>
#include <iostream>
#include <numeric>
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
    i64 n;
    cin >> n;
    vector<double> p_arr(n);
    for (int i = 0; i < n; i++) {
        cin >> p_arr[i];
    }
    array<vector<double>, 2> dp{vector<double>(n + 1), vector<double>(n + 1)};
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            dp[1][j + 1] += dp[0][j] * p_arr[i];
            dp[1][j] += dp[0][j] * (1 - p_arr[i]);
        }
        swap(dp[0], dp[1]);
        fill(all(dp[1]), 0);
    }
    double ans = accumulate(bg(dp[0]) + (n + 1) / 2, dp[0].end(), double(0));
    printf("%.10lf", ans);
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
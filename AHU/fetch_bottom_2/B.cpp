#include <cstdio>
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
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    i64 n;
    cin >> n;
    vector<vector<double>> ai(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ai[i][j];
        }
    }
    i64            N = 1 << n;
    vector<double> dp(N);
    dp[N - 1] = 1;
    for (int i = N - 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {  // j是被吃
            if (i >> j & 1) continue;
            for (int k = 0; k < n; k++) {
                if (!(i >> k & 1)) continue;
                dp[i] += dp[i | (1 << j)] * ai[k][j];
            }
        }
        dp[i] /= (__builtin_popcount(i) * (__builtin_popcount(i) + 1));
        dp[i] *= 2;
    }
    for (int i = 0; i < n; i++) {
        printf("%.8lf ", dp[1 << i]);
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
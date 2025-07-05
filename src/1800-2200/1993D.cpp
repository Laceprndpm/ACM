#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;
using i16  = int16_t;
using u16  = uint16_t;
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
    i64 n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> sorted_arr = arr;
    sor(sorted_arr);
    int  blocks          = (n - 1) / k;
    int  remain          = n - k * blocks;
    auto checker_factory = [&]() -> function<bool(int)> {
        // auto check1 = [&](int val) -> bool {
        //     vector<vector<u16>> dp_keep(n + 1, vector<u16>(remain + 1, UINT16_MAX));
        //     dp_keep[0][0] = 0;
        //     for (int i = 0; i < n; i++) {
        //         for (int j = 0; j <= remain; j++) {
        //             if (j + 1 <= remain)
        //                 dp_keep[i + 1][j + 1] =
        //                     min<u16>(dp_keep[i + 1][j + 1], dp_keep[i][j] + (u16)(arr[i] < val ? 1 : 0));
        //             if (i + k <= n) dp_keep[i + k][j] = min(dp_keep[i + k][j], dp_keep[i][j]);
        //         }
        //     }
        //     return dp_keep[n][remain] <= (remain - 1) / 2;
        // };
        // auto check2 = [&](int val) -> bool {
        //     vector<vector<u16>> dp_block(n + 1, vector<u16>(blocks + 1, UINT16_MAX));
        //     dp_block[0][0] = 0;
        //     for (int i = 0; i < n; i++) {
        //         for (int j = 0; j <= blocks; j++) {
        //             dp_block[i + 1][j] = min<u16>(dp_block[i + 1][j], dp_block[i][j] + (arr[i] < val ? 1 : 0));
        //             if (i + k <= n && j + 1 <= blocks)
        //                 dp_block[i + k][j + 1] = min(dp_block[i + k][j + 1], dp_block[i][j]);
        //         }
        //     }
        //     return dp_block[n][blocks] <= (remain - 1) / 2;
        // };
        // debug
        // return check2;
        auto check3 = [&](int val) -> bool {
            vector<int> brr(n);
            for (int i = 0; i < n; i++) {
                brr[i] = (arr[i] < val ? 1 : -1);
            }
            vector<int> dp(n);
            for (int i = 0; i < n; i++) {
                if (i % k == 0) {
                    if (i == 0) {
                        dp[i] = brr[i];
                        continue;
                    }
                    dp[i] = min(brr[i], dp[i - k]);
                    continue;
                }
                dp[i] = dp[i - 1] + brr[i];
                if (i < k) continue;
                dp[i] = min(dp[i], dp[i - k]);
            }
            return dp[n - 1] < 0;
        };
        return check3;
        // if (remain < blocks) {
        //     return check1;
        // } else {
        //     return check2;
        // }
    };

    auto checker = checker_factory();
    int  l = 0, r = n - 1;
    int  ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (checker(sorted_arr[mid])) {
            ans = sorted_arr[mid];
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
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
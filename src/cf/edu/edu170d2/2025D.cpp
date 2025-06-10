#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
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
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    arr.push_back(0);
    vector<vector<int>> dp(2, vector<int>(m + 50));  // 智力水平
    vector<int>         meet;
    int                 cnt = 0;
    for (int i = 0; i <= n; i++) {
        if (arr[i] == 0) {
            sor(meet);
            // int l   = lower_bound(all(meet), -cnt) - bg(meet);  // l >= -cnt
            // int r   = lower_bound(all(meet), 0) - bg(meet);
            int l = 0, r = 0;
            int len = sz(meet);
            for (int j = 0; j <= cnt; j++) {  // 枚举智力
                while (r != len && meet[r] <= j) {
                    r++;
                }
                while (l < len && l < r && meet[l] < j - cnt) {
                    l++;
                }
                dp[1][j]     = max(dp[0][j] + r - l, dp[1][j]);
                dp[1][j + 1] = max(dp[0][j] + r - l, dp[1][j + 1]);
            }
            swap(dp[0], dp[1]);
            fill(all(dp[1]), 0);
            meet.clear();
            cnt++;
        } else {
            meet.push_back(arr[i]);
        }
    }
    cout << *max_element(all(dp[0]));
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
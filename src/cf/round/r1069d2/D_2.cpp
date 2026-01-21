#include <iostream>
#include <vector>
using namespace std;
using ll = long long;

constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>         arr(n);
    vector<vector<int>> dp(k + 1, vector<int>(k + 1, -INF));
    dp[k][0] = 0;
    for (int& i : arr) cin >> i;
    int maxn     = 0;
    int need_add = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= maxn) {
            need_add++;
            continue;
        }
        maxn = arr[i];
        if (need_add) {
            for (int i = 0; i <= k; i++) {
                for (int j = 0; j <= k - i; j++) {
                    dp[i][j] += j * need_add;
                }
            }
        }
        need_add = 0;
        vector<int> tmp_dp(k + 1, -INF);
        for (int x = 0; x <= k; x++) {
            for (int y = 0; y <= k - x; y++) {
                tmp_dp[x] = max(tmp_dp[x], dp[x][y]);
            }
        }
        for (int x = 0; x <= k; x++) {
            for (int y = 0; y <= min(x, arr[i]); y++) {
                dp[x - y][y] = max(dp[x - y][y], tmp_dp[x]);
            }
        }
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k - i; j++) {
                dp[i][j] += j;
            }
        }
    }
    if (need_add) {
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k - i; j++) {
                dp[i][j] += j * need_add;
            }
        }
    }
    int res = 0;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k - i; j++) {
            res = max(res, dp[i][j]);
        }
    }
    cout << res << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

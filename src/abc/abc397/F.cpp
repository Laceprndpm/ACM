#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<int> dpMp1(n + 1);
    vector<int> dpMp3(n + 1);
    set<int>    Mp1;
    for (int i = 1; i <= n; i++) {
        Mp1.insert(arr[i]);
        dpMp1[i] = Mp1.size();
    }
    set<int> Mp3;
    for (int i = n; i >= 1; i--) {
        Mp3.insert(arr[i]);
        dpMp3[i] = Mp3.size();
    }
    vector<int> dp(n + 1);
    set<int>    cur;
    dp[1] = -INF;
    for (int i = 2; i <= n - 1; i++) {
        dp[i] = dpMp1[i - 1] + dpMp3[i + 1] + 1;
        if (!cur.contains(arr[i])) {
            if (dp[i] < dp[i - 1] - dpMp3[i] + dpMp3[i + 1] + 1) {
                dp[i] = dp[i - 1] - dpMp3[i] + dpMp3[i + 1] + 1;
                cur.insert(arr[i]);
            } else {
                cur.clear();
                cur.insert(arr[i]);
            }
        } else {
            if (dp[i] < dp[i - 1] - dpMp3[i] + dpMp3[i + 1]) {
                dp[i] = dp[i - 1] - dpMp3[i] + dpMp3[i + 1];
            } else {
                cur.clear();
                cur.insert(arr[i]);
            }
        }
    }
    cout << *max_element(dp.begin() + 2, dp.begin() + n);
    return 0;
}

// 8 9-13 14
// 7 + 5 + 2
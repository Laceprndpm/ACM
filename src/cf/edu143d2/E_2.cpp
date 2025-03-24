#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

vector<i64> DynamicPlan(const vector<i64>& brr)
{
    int         n = brr.size() - 1;
    vector<i64> dp(n + 1);
    stack<i64>  monoStack;
    // 单调栈获取第一个小于的，其他大于的默认全部削成brr - i
    // 如果有小于的，则可以dp来减少计算量
    // 这题dp妙在状态转移，可以由第一个无法被削的塔尖进行转移
    for (int i = 1; i <= n; i++) {
        while (!monoStack.empty() && brr[monoStack.top()] >= brr[i]) {
            monoStack.pop();
        }
        if (monoStack.empty()) {
            i64 b   = (brr[i] + i);
            i64 a   = max((brr[i] + 1), 0ll);
            i64 val = (b - a + 1) * (b + a) / 2;
            dp[i]   = val;
        } else {
            // 等差数列
            i64 idxSmall = monoStack.top();
            i64 b        = (brr[i] + i);
            i64 a        = brr[i] + idxSmall + 1;
            i64 val      = (b - a + 1) * (b + a) / 2 + dp[idxSmall];
            dp[i]        = val;
        }
        monoStack.push(i);
    }
    for (int i = 1; i <= n; i++) {
        dp[i] -= brr[i] + i;
    }
    return dp;
}

void solve()
{
    int n;
    cin >> n;
    vector<i64> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<i64> brr(n + 1);
    for (int i = 1; i <= n; i++) {
        brr[i] = arr[i] - i;
    }
    vector<i64> dpLeft = DynamicPlan(brr);
    reverse(arr.begin() + 1, arr.end());
    for (int i = 1; i <= n; i++) {
        brr[i] = arr[i] - i;
    }
    vector<i64> dpRight = DynamicPlan(brr);
    reverse(dpRight.begin() + 1, dpRight.end());
    i64 sumVal = 0;
    for (int i = 1; i <= n; i++) {
        sumVal += arr[i];
    }
    i64 highValue = 0;
    for (int i = 1; i <= n; i++) {
        highValue = max(highValue, dpLeft[i] + dpRight[i]);
    }
    cout << sumVal - highValue << '\n';
}

signed main(int argc, char** argv)
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
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

constexpr int INF = 1e9;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<i64> hi(n + 1);  // 读入每个点的高度
    for (int i = 1; i <= n; i++) {
        cin >> hi[i];
    }
    vector<i64> dp(n + 1, INF);  // 初始化为无穷大
    dp[1] = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = max(i - k, 1); j <= i; j++) {  // 对每个点，向后转移
            dp[i] = min(dp[i], dp[j] + abs(hi[i] - hi[j]));
        }
    }
    cout << dp[n] << '\n';
    return 0;
}

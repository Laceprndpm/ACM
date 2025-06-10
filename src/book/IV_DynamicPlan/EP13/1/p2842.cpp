#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, w;
    cin >> n >> w;
    vector<int> dp(w + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        for (int j = cur; j <= w; j++) {
            dp[j] = min(dp[j], dp[j - cur] + 1);
        }
    }
    cout << dp[w];
    return 0;
}
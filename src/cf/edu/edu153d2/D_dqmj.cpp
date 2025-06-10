#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ll   long long

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int n  = s.size();
    int z1 = 0;
    for (int i = 0; i <= n - 1; i++) {
        if (s[i] == '1') {
            z1++;
        }
    }
    int                 z0  = n - z1;
    int                 sum = (n * (n - 1) / 2 - z0 * (z0 - 1) / 2 + (z1 * (z1 - 1) / 2)) / 2;
    vector<vector<int>> dp(z1 + 1, vector<int>(sum + 1, 1e9));  // 当前1数量，10 11的数量
    // Initialization is already done in the vector declaration
    dp[0][0] = 0;
    for (int i = 0; i <= n - 1; i++) {
        for (int j = z1 - 1; j >= 0; j--) {
            for (int e = 0; e + i <= sum; e++) {
                dp[j + 1][e + i] = min(dp[j + 1][e + i], dp[j][e] + (s[i] == '0'));
            }
        }
    }
    cout << dp[z1][sum] << endl;
    return 0;
}

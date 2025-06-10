#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;
int dp[1005];
int ndp[1005];

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            int cur;
            cin >> cur;
            if (j == 0) {
                dp[j] = ndp[j] + cur;
            } else if (j == i) {
                dp[j] = ndp[j - 1] + cur;
            } else {
                dp[j] = max(ndp[j - 1] + cur, ndp[j] + cur);
            }
        }
        swap(dp, ndp);
    }
    cout << *max_element(ndp, ndp + n);
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;
// 已经选了i个位置，j个物种后
int dp[65][65];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        int spe;
        cin >> spe;
        cnt[spe]++;
    }
    vector<int> spe2rank(70);
    vector<int> rank2spe(70);

    int rank = 0;

    for (auto iter : cnt) {
        rank++;
        spe2rank[rank] = iter.first;
    }

    int remain = cnt.size();
    for (int j = 1; j <= rank; j++) {                          // 第j个物种
        for (int i = 1; i <= min(cnt[spe2rank[j]], k); i++) {  // 选择i个
            for (int ii = 60; ii >= 1; ii++) {                 // 现在ii个
                dp[ii][j] = dp[ii - i][j - 1]*;
            }
        }
    }
    return 0;
}
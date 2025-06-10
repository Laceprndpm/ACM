#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct item {
    i64 weight;
    i64 val;
};

void solve()
{
    i64 n, w, k;
    cin >> n >> w >> k;
    vector<item> items(n + 1);
    auto         cmp = [&](const item& a, const item& b) {
        return (a.weight < b.weight);
    };

    for (int i = 1; i <= n; i++) {
        cin >> items[i].weight >> items[i].val;
    }

    sort(items.begin() + 1, items.end(), cmp);
    vector<vector<i64>> dp(n + 1, vector<i64>(w + 1));
    for (i64 i = 1; i <= n; i++) {
        for (i64 j = 0; j <= w; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= items[i].weight) {
                dp[i][j] = max({dp[i - 1][j - items[i].weight] + items[i].val, dp[i][j], dp[i][j - 1]});
            }
        }
    }
    i64                                         curSum = 0;
    priority_queue<i64, vector<i64>, greater<>> pq;
    vector<i64>                                 free(n + 2);
    for (i64 i = n; i >= 1; i--) {
        pq.push(items[i].val);
        curSum += items[i].val;
        if ((i64)pq.size() > k) {
            curSum -= pq.top();
            pq.pop();
        }
        free[i] = curSum;
    }
    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(dp[i][w] + free[i + 1], ans);
    }
    cout << ans << '\n';
    // map<tuple<i64, i64, i64>, i64> mp;
    // function<i64(i64, i64, i64)>   dfs = [&](i64 th, i64 remainM, i64 remainK) -> i64 {
    //     if (mp.count({th, remainM, remainK})) {
    //         return mp[{th, remainM, remainK}];
    //     }
    //     if (th == n) {
    //         return 0;
    //     }

    //     i64 ans = 0;
    //     if (remainK) {
    //         ans = items[th].val + dfs(th + 1, remainM, remainK - 1);
    //     } else {
    //         ans = dfs(th + 1, remainM, remainK);
    //     }

    //     if (remainM >= items[th].weight) {
    //         ans = max(ans, items[th].val + dfs(th + 1, remainM - items[th].first, remainK));
    //     }
    //     return mp[{th, remainM, remainK}] = ans;
    // };
    // i64 ans = dfs(0, w, k);
    // cout << ans << '\n';
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
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
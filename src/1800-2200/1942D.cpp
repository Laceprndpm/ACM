#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <set>
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

struct Node {
    i64 val;
    i64 topval;
    i64 idx;
    i64 dpIdx;

    bool operator<(const Node& other) const
    {
        return val + topval < other.val + other.topval;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<i64>>          dp(n + 1);
    vector<priority_queue<Node>> dp2(n + 1);
    dp[0].pb(0);
    vector<vector<i64>> bd(n + 1, vector<i64>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> bd[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i != 1) {
            while (!dp2[i - 2].empty() && dp[i - 2].size() < k) {
                auto cur = dp2[i - 2].top();
                dp2[i - 2].pop();
                dp[i - 2].push_back(cur.val + cur.topval);
                if (cur.idx + 1 < min(1 << cur.dpIdx, k)) {
                    dp2[i - 2].push({cur.val, dp[cur.dpIdx][cur.idx], cur.idx + 1, cur.dpIdx});
                }
            }
        }
        if (i == 1)
            for (int j = i; j <= n; j++) {
                i64 val = bd[i][j];
                dp2[j].push({val, dp[i - 1][0], 0, i - 1});
            }
        if (i != 1) {
            for (int j = i; j <= n; j++) {
                i64 val = bd[i][j];
                dp2[j].push({val, dp[i - 2][0], 0, i - 2});
            }
        }
        dp2[i].push({0, dp[i - 1][0], 0, i - 1});
    }
    while (!dp2[n].empty() && dp[n].size() < k) {
        auto cur = dp2[n].top();
        dp2[n].pop();
        dp[n].push_back(cur.val + cur.topval);
        if ((cur.dpIdx > 30 && cur.idx + 1 < k) || ((cur.idx < 30) && cur.idx + 1 < min(1 << cur.dpIdx, k))) {
            dp2[n].push({cur.val, dp[cur.dpIdx][cur.idx + 1], cur.idx + 1, cur.dpIdx});
        }
    }
    for (int i = 0; i < k; i++) {
        cout << dp[n][i] << ' ';
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
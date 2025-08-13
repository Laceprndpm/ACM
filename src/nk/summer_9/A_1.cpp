#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>
int MAXH = 30;

void Echo2()
{
    // 一颗结点数为n的AVL树树高最多为logn级别
    int n;
    cin >> n;
    vector<pii> tr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> tr[i].first >> tr[i].second;
    }
    vector<int>        siz(n + 1);
    function<int(int)> dfs1 = [&](int cur) -> int {
        if (cur == 0) return 0;
        siz[cur] = 1;
        siz[cur] += dfs1(tr[cur].first);
        siz[cur] += dfs1(tr[cur].second);
        return siz[cur];
    };
    dfs1(1);
    // 用dp_i_h表示以i为根的子树构建一颗高为hAVL树的最小操作次数
    vector<vector<int>> dp(n + 1, vector<int>(30));
    vector<int>         addAVL(30);
    addAVL[0] = 0;
    addAVL[1] = 1;
    for (int h = 2; h < 30; h++) {
        addAVL[h] = 1 + addAVL[h - 1] + addAVL[h - 2];
    }
    function<void(int)> dfs2 = [&](int cur) -> void {
        if (cur == 0) return;
        dfs2(tr[cur].first);
        dfs2(tr[cur].second);
        dp[cur][0] = siz[cur];
        for (int h = 1; h <= 30; h++) {
            int res = inf;
            // 左右子树高度一样
            int L     = h - 1;
            int R     = h - 1;
            int costL = (tr[cur].first == 0 ? addAVL[L] : dp[tr[cur].first][L]);
            int costR = (tr[cur].second == 0 ? addAVL[R] : dp[tr[cur].second][R]);
            res       = min(res, costL + costR);
            if (h >= 2) {  // 枚举高度差1的情况
                L     = h - 2;
                R     = h - 1;
                costL = (tr[cur].first == 0 ? addAVL[L] : dp[tr[cur].first][L]);
                costR = (tr[cur].second == 0 ? addAVL[R] : dp[tr[cur].second][R]);
                res   = min(res, costL + costR);
                L     = h - 1;
                R     = h - 2;
                costL = (tr[cur].first == 0 ? addAVL[L] : dp[tr[cur].first][L]);
                costR = (tr[cur].second == 0 ? addAVL[R] : dp[tr[cur].second][R]);
                res   = min(res, costL + costR);
            }
            dp[cur][h] = res;
        }
    };
    dfs2(1);
    int ans = inf;
    for (int h = 0; h < 30; h++) {
        ans = min(ans, dp[1][h]);
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--) Echo2();
}
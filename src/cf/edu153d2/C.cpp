#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

// dp[i]如果为1，说明在这里开始，后手必赢
// 如果存在aj<ai，j<i，dp[j]==0，则dp[i]==1
// 所以我需要直到aj最小值

// min2为后手想赢必须大于的值

// 假设到了i处，前面有i-1个数，其中a处为先手必赢，b处为后手必

int lowbit(int x)
{
    return x & -x;
}

void update(vector<int> &bit, int x, int v)
{
    for (int i = x; i < bit.size(); i += lowbit(i)) {
        bit[i] += v;
    }
}

int query(vector<int> &bit, int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) {
        res += bit[i];
    }
    return res;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>  bits(n + 1, 0);
    vector<bool> dp(n + 1);
    int          curentMin  = n + 1;
    int          curentMin2 = n + 1;
    int          ans        = 0;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        if (cur < curentMin) {  // 终点站，后手必赢
            dp[i]     = 1;
            curentMin = cur;
        } else if (cur > curentMin2) {
            
        } else {
            ans++;
            curentMin2 = min(cur, curentMin2);
        }
    }
    cout << ans << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
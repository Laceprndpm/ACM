#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n, m;
    cin >> n >> m;
    set<int>            bad;
    set<int>            color;
    vector<vector<int>> input(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cur;
            cin >> cur;
            input[i][j] = cur;
            color.insert(cur);
            if (cur == input[i - 1][j] || cur == input[i][j - 1]) {
                bad.insert(cur);
            }
        }
    }
    if (color.size() == 1) {
        cout << 0 << '\n';
        return;
    }
    i64 badsove = max((i64)bad.size() - 1, 0LL);
    i64 ans     = badsove * 2;
    ans += ((i64)color.size() - badsove - 1);
    cout << ans << '\n';
}

signed main(int argc, char** argv)
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
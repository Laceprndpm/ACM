#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

void solve()
{
    LL n;
    cin >> n;
    LL ans = 1;
    while (n > 3) {
        ans *= 2;
        n /= 4;
    }
    cout << ans << '\n';
}

signed main()
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
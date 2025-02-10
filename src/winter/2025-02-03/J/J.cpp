#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve(void)
{
    int n, m;
    cin >> n >> m;
    if (n % 3 == 0 || m % 3 == 0) {
        cout << n * m / 3 << '\n';
        return;
    }
    int ans = 0;
    ans += n / 3 * m;
    n %= 3;
    ans += m / 3 * n;
    m %= 3;
    ans += n * m / 2;
    if (n == 1 && m == 1) {
        ans++;
    }
    cout << ans << '\n';
    return;
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
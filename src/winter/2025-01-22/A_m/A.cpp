#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void solve(void)
{
    int a, b;
    cin >> a >> b;
    if (a == 1 && b == 1)
    {
        cout << 1 << '\n';
        return;
    }
    cout << b - a << '\n';
    return;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
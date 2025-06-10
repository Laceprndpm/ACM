#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, sum;
    cin >> n;
    int cnt;
    cin >> cnt;
    int ans = cnt;
    for (int i = 2; i <= n; ++i)
    {
        int a;
        cin >> a;
        cnt = max(cnt + a, a);
        ans = max(ans, cnt);
    }
    cout << ans;
    return 0;
}
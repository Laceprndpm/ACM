#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void solve(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n / 2 - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << b << ' ' << -a << ' ';
    }
    if (n % 2 == 1)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a + b == 0)
        {
            if (a + c == 0)
            {
                cout << c + b << ' ' << -a << ' ' << -a;
            }
            else
            {
                cout << -b << ' ' << a + c << ' ' << -b;
            }
        }
        else
        {
            cout << -c << ' ' << -c << ' ' << a + b;
        }
    }
    else
    {
        int a, b;
        cin >> a >> b;
        cout << b << ' ' << -a << ' ';
    }
    cout << '\n';
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
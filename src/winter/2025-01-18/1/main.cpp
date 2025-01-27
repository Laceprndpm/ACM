#include <bits/stdc++.h>
using namespace std;
#define int long long

int t;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while (t--)
    {
        int n, k, b, s;
        cin >> n >> k >> b >> s;

        if (n * (k - 1) + b * k < s || b * k > s)
        {
            cout << -1 << '\n';
            continue;
        }
        else
        {
            int remain = s;
            for (int i = 1; i <= n; i++)
            {
                int temp = 0;
                if (b != 0)
                {
                    temp += b * k;
                    remain -= b * k;
                    b = 0;
                }

                if (remain >= k - 1)
                {
                    temp += k - 1;
                    remain -= k - 1;
                }
                else
                {
                    temp += remain;
                    remain = 0;
                }
                cout << temp << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
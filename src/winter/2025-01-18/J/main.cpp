#include <bits/stdc++.h>
using namespace std;
#define int long long
using ll = long long;
using ull = unsigned long long;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n, l, t;
        ll P;
        cin >> n >> P >> l >> t;
        int tasks = n / 7 + (n % 7 != 0 ? 1 : 0);
        int days = 0;
        {
            int full_day = 0;
            ll full_power = l + t * 2;
            full_day = min((P / full_power) + (P % full_power != 0 ? 1 : 0), (ll)(tasks / 2));
            P -= full_day * full_power;
            days += full_day;
            tasks -= full_day * 2;
        }
        {
            if (P > 0)
            {
                if (tasks != 0)
                {
                    days++;
                    P -= l + t;
                }
            }
            if (P > 0)
            {
                days += P / l + (P % l != 0 ? 1 : 0);
            }
        }
        // ll full_day = min((P / full_power) + ((P % full_power != 0) ? 1 : 0), (ll)tasks / 2);
        // P -= full_day * full_power;
        // days += full_day;

        // if (tasks % 2 == 1 && P > 0)
        // {
        //     P -= t + l;
        //     days++;
        // }
        // if (P > 0)
        //     days += (P / l) + (P % l != 0 ? 1 : 0);
        cout << n - days << '\n';
    }
    return 0;
}
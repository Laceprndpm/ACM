#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e6 + 5;
int n, H;
signed a[N];
int prefix_full[N], prefix_half[N];
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> H;
    int h = H;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int j = 0;
    for (int i = 1; i <= n; i++)
    {
        prefix_full[i] = a[i] + prefix_full[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        prefix_half[i] = (a[i] + 1) / 2 + prefix_half[i - 1];
    }

    while (h > 0)
    {
        j++;
        // if (h - prefix_full[n] >= H / 2) // 可以直接走完
        // {
        //     h -= prefix_full[n];
        //     continue;
        // }

        // if (h - prefix_half[n] > 0 && h <= H / 2) // 可以直接半数走完
        // {
        //     h -= prefix_half[n];
        //     continue;
        // }

        // if (h > H / 2 && h - prefix_full[n] <= H / 2) // 能走一点
        // {
        //     int damage = h - H / 2;
        //     int half_place = lower_bound(prefix_full + 1, prefix_full + n + 1, damage) - prefix_full; // 在受到第n次攻击时，进入二阶段
        //     h -= prefix_full[half_place];
        //     i = half_place;

        //     auto end = lower_bound(prefix_half + 1, prefix_half + n + 1, h);
        //     if (end != prefix_half + n + 1)
        //     {
        //         for (i = i + 1; i <= n; i++)
        //         {
        //             h -= (a[i] + 1) / 2;
        //             if (h <= 0)
        //             {
        //                 cout << j << ' ' << i << '\n';
        //                 return 0;
        //             }
        //         }
        //     }
        //     else
        //     {
        //         h -= prefix_half[n] - prefix_half[half_place];
        //     }
        //     continue;
        // }

        for (int i = 1; i <= n; i++)
        {
            if (h <= H / 2)
            {
                h -= (a[i] + 1) / 2;
            }
            else
            {
                h -= a[i];
            }
            if (h <= 0)
            {
                cout << j << ' ' << i << '\n';
                return 0;
            }
            continue;
        }
    }
    return 0;
}
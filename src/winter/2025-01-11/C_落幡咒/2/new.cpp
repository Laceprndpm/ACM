#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 5e6 + 5;
long long n, H;
signed a[N];
long long prefix_full[N], prefix_half[N];

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
    for (int i = 1; i <= n; i++)
    {
        prefix_full[i] = a[i] + prefix_full[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        prefix_half[i] = (a[i] + 1) / 2 + prefix_half[i - 1];
    }

    int i = 1, j = 0;
    while (true)
    {
        if (h <= 0)
        {
            if (j == 0)
            {
                i--;
                j = n;
            }
            cout << i << ' ' << j << endl;
            return 0;
        }

        if (h > H / 2)
        {
            if (h - prefix_full[n] >= H / 2)
            {
                // i++;
                // h -= prefix_full[n];
                int damage = h - H / 2;
                int loops = damage / prefix_full[n];
                h -= loops * prefix_full[n];
                i += loops;
            }
            else
            {
                int damage = h - H / 2;
                int half_place = lower_bound(prefix_full + j + 1, prefix_full + n + 1, damage) - prefix_full;
                h -= (prefix_full[half_place] - prefix_full[j]);
                j = half_place;
            }
        }
        else
        {
            if (h - prefix_half[n] >= 0)
            {
                // i++;
                // h -= prefix_half[n];
                int damage = h;
                int loops = damage / prefix_half[n];
                h -= loops * prefix_half[n];
                i += loops;
            }
            else
            {
                int damage = h;
                int full_place = lower_bound(prefix_half + j + 1, prefix_half + n + 1, damage) - prefix_half;
                if (full_place == n + 1)
                {
                    h -= prefix_half[n] - prefix_half[j];
                    i++;
                    j = 0;
                    continue;
                }
                h -= (prefix_half[full_place] - prefix_half[j]);
                j = full_place;
            }
        }
    }
    return 0;
}
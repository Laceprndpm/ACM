#include <bits/stdc++.h>

#include <cmath>
#include <cstring>
#include <map>
#include <vector>
using namespace std;
#define MAXN 20010
int       n, m, a[MAXN], b[MAXN], f[MAXN * 2], d[MAXN * 2];
long long c[MAXN * 2];
using i64 = long long;

long long calcsqrt(long long x)
{
    long long l, r, mid;
    l = 0;
    r = 1000000001;
    while (r - l > 1) {
        mid = (l + r) / 2;
        if (mid * mid <= x)
            l = mid;
        else
            r = mid;
    }
    return l;
}

i64 helper(const vector<int> &x, const vector<int> &r)
{
    long long ans  = 0;
    int       dtop = 0;
    int       ctop = 0;
    for (int i = 1; i <= n; i++) {
        a[i]      = x[i] - r[i];
        b[i]      = x[i] + r[i] + 1;
        d[++dtop] = a[i];
        d[++dtop] = b[i];
    }
    sort(d + 1, d + dtop + 1);
    for (int i = 1; i <= dtop; i++) {
        if (d[i] != d[i - 1] || i == 1) c[++ctop] = d[i];
    }
    for (int i = 1; i <= n; ++i) {
        int x = lower_bound(c + 1, c + ctop + 1, a[i]) - c;
        int y = lower_bound(c + 1, c + ctop + 1, b[i]) - c;
        for (int j = x; j < y; j++) {
            f[j] = 1;
        }
    }
    for (int i = 1; i < ctop; i++) {
        if (f[i]) ans += c[i + 1] - c[i];
    }
    memset(f, 0, (ctop + 1) * sizeof(int));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        vector<int>   x(n + 1);
        vector<int>   r(n + 1);
        map<int, int> mp;
        for (int i = 1; i <= n; i++) {
            cin >> x[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> r[i];
        }
        i64 ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int plac = x[i] - r[i]; plac <= x[i] + r[i]; plac++) {
                int y = sqrt((i64)r[i] * r[i] - (i64)(x[i] - plac) * (x[i] - plac));
                if (mp[plac] < y * 2 + 1) {
                    ans += y * 2 + 1 - mp[plac];
                    mp[plac] = y * 2 + 1;
                }
            }
        }
        cout << ans << '\n';
        //     vector<int> newr(n + 1);
        // for (int i = 1; i <= n; i++) {
        //     cin >> x[i];
        // }
        // for (int i = 1; i <= n; i++) {
        //     cin >> r[i];
        // }

        //     i64  ans  = helper(x, r);
        //     bool flag = true;
        //     int  curh = 1;
        //     while (flag) {
        //         flag = false;
        //         for (int i = 1; i <= n; i++) {
        //             if (r[i] - curh >= 0) {
        //                 flag    = true;
        //                 newr[i] = sqrt(r[i] * r[i] - curh * curh);
        //             } else {
        //                 x[i] = x[n];
        //                 r[i] = r[n];
        //                 n--;
        //                 i--;
        //             }
        //         }
        //         ans += 2 * helper(x, newr);
        //         curh++;
        //     }
        //     cout << ans << '\n';
        // }
    }
    return 0;
}
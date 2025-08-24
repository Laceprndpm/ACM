#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    int         mi = inf;
    int         mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mi = min(mi, a[i]);
        mx = max(mx, a[i]);
    }
    int ans = 0;
    int lst = 0;
    for (int i = 1; i <= n; i++) {
        ans += max(0ll, mx - a[i] - lst);
        lst = mx - a[i];
    }
    if (m == 1) {
        cout << ans << '\n';
        return;
    } else {
        for (int i = mi; i < mx; i++) {
            int         res = 0;
            vector<int> tmp(n + 1);
            for (int j = 1; j <= n; j++) {
                if (a[j] <= i) {
                    tmp[j] = i - a[j];
                } else {
                    tmp[j] = mx - a[j];
                }
            }
            for (int j = 1; j <= n; j++) {
                res += max(0ll, tmp[j] - tmp[j - 1]);
            }
            ans = min(ans, res);
        }
        cout << ans << '\n';
    }
}

// 6 2
// 1 8 1 8 8 15

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--) Echo2();
}
#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

void solve()
{
    LL l, r, G;
    cin >> l >> r >> G;
    LL Lfactor = (l - 1) / G + 1;
    LL Rfactor = r / G;
    if (Lfactor == Rfactor && Lfactor == 1) {
        cout << G << ' ' << G << '\n';
        return;
    }
    if (Lfactor >= Rfactor) {
        cout << -1 << ' ' << -1 << '\n';
        return;
    }
    for (LL dis = Rfactor - Lfactor; dis > 0; dis--) {
        for (LL i = Lfactor; i + dis <= Rfactor; i++) {
            if (gcd(i, i + dis) == 1) {
                cout << i * G << ' ' << (i + dis) * G << '\n';
                return;
            }
        }
    }
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
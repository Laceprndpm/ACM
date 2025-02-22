#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long

void Echo2()
{
    int m, k, a, b;
    cin >> m >> k >> a >> b;
    m -= a;
    if (m <= 0) {
        cout << 0 << '\n';
        return;
    }
    int ans  = 0;
    int need = m / k;
    ans += max(0ll, need - b);
    b -= need;
    m -= need * k;
    if (k - m <= a) {
        if (b <= 0) ans++;
    } else {
        ans += m;
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        Echo2();
}
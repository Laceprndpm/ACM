#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int m, k, a1, a2;
    cin >> m >> k >> a1 >> a2;
    int type2CoinsNowUse = min(m / k, a2);
    m -= type2CoinsNowUse * k;
    if (m <= a1) {
        cout << "0\n";
        return;
    } else {
        int rest      = m - a1;
        int kFancyMax = m / k;
        int kFancy    = min(((rest - 1) / k + 1), kFancyMax);
        m -= kFancy * k;
        int oneFancy = max(m - a1, 0);
        cout << oneFancy + kFancy << '\n';
        return;
    }
}

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
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
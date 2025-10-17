#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 *@Spell : Lucas, math
 */
int comb(int n, int m)
{
    if (n < m) return 0;
    if (n >= 2 || m >= 2) {
        return comb(n / 2, m / 2) * comb(n % 2, m % 2);
    }
    return 1;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    n--;
    for (int i = 0; i <= n; i++) {
        cout << comb(n, i) * k << ' ';
    }
    cout << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
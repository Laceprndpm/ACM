#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n;
    cin >> n;
    int m   = n / 15;
    int ans = m * 3;
    if (n % 15 == 0) {
        ans += 1;
    } else if (n % 15 == 1) {
        ans += 2;
    } else if (n % 15 >= 2) {
        ans += 3;
    }
    cout << ans << '\n';
    return;
}

signed main(int argc, char** argv)
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
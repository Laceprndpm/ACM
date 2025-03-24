#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    i64 a1, a2, a3, a4;
    cin >> a1 >> a2 >> a3 >> a4;
    i64 ans = 0;
    ans += a1;
    i64 balance = min(a2, a3);
    a2 -= balance;
    a3 -= balance;
    ans += balance * 2ll;
    if (a1 == 0) {
        cout << 1 << '\n';
        return;
    }
    i64 mood = a1;
    i64 a5   = max(a2, a3);
    if (a5 > mood) {
        ans += mood + 1;
    } else {
        ans += a5;
        mood -= a5;
        ans += min(mood + 1, a4);
    }
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
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
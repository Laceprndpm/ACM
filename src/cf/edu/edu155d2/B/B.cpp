#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    i64 ans1 = 0;
    i64 min1 = 1e9 + 2;
    for (int i = 0; i < n; i++) {
        i64 tmp;
        cin >> tmp;
        ans1 += tmp;
        min1 = min(min1, tmp);
    }
    i64 ans2 = 0;
    i64 min2 = 1e9 + 2;
    for (int i = 0; i < n; i++) {
        i64 tmp;
        cin >> tmp;
        ans2 += tmp;
        min2 = min(min2, tmp);
    }
    cout << min(ans1 + min2 * n, ans2 + min1 * n) << '\n';
}

signed main(int argc, char** argv)
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
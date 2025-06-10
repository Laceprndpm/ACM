#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n;
    cin >> n;
    int  ans = 0;
    char pre;
    cin >> pre;
    if (pre == '1')
        ans++;
    for (int i = 1; i < n; i++) {
        char cur;
        cin >> cur;
        if (pre == cur) {
            continue;
        } else {
            pre = cur;
            ans++;
        }
    }
    cout << ans << '\n';
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
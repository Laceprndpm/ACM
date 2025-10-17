#include <iostream>
using namespace std;
using i64 = long long;
// B
void solve()
{
    int    n;
    string s;
    cin >> n;
    cin >> s;
    i64 cnt1 = 0, cnt2 = 0;
    for (char c : s) {
        if (c == '-') {
            cnt1++;
        } else {
            cnt2++;
        }
    }
    i64 ans = (cnt1 / 2) * (cnt1 - cnt1 / 2) * cnt2;
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

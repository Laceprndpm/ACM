#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{

    string s;
    cin >> s;
    int n   = s.length();
    int ans = 0;
    for (int length = n / 2 * 2; length >= ans; length -= 2) {
        for (int l = 0; l + length <= n; l++) {
            bool OK        = true;
            int  badperson = -1;
            for (int i = 0; i < length / 2; i++) {
                if (s[i + l] != s[i + l + length / 2] && s[i + l] != '?' && s[i + l + length / 2] != '?') {
                    OK        = false;
                    badperson = i + l;
                    break;
                }
            }
            if (OK) {
                ans = max(ans, length);
            } else {
                l = badperson;
            }
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
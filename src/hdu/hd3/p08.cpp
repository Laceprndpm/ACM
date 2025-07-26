#include <bits/stdc++.h>

#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>
using namespace std;

#define endl '\n'
#define ll   long long

signed main(int argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    srand(time(0));
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    // 110100
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int nmd = 0;
        for (nmd = 0; nmd + 1 < n; nmd++) {
            if (s[nmd] == s[nmd + 1]) break;
        }
        string s1   = string(s.begin(), s.begin() + nmd + 1);
        string s2   = string(s.begin() + nmd + 1, s.end());
        s           = s2 + s1;
        string ns   = s;
        int    ans  = 1e9;
        int    ans1 = 0, ans2 = 0;
        for (int i = 0; i <= n - 1; i++) {
            if (s[i] - '0' == i % 2) {
                continue;
            } else {
                if (i <= n - 2 && s[i + 1] != s[i]) {
                    swap(ns[i], ns[i + 1]);
                    i++;
                    ans1++;
                } else {
                    ns[i] = !(ns[i] - '0') + '0';
                    ans1++;
                }
            }
        }

        for (int i = 0; i <= n - 1; i++) {
            if (s[i] - '0' == (i + 1) % 2) {
                continue;
            } else {
                if (i <= n - 2 && s[i + 1] != s[i]) {
                    swap(ns[i], ns[i + 1]);
                    i++;
                    ans2++;
                } else {
                    ans2++;
                }
            }
        }
        ans = min(ans1, ans2);
        cout << ans << endl;
    }
    return 0;
}

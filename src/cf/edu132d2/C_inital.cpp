#include <algorithm>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    {
        int cnt  = 0;
        int cnt2 = 0;
        for (char i : s) {
            if (i == '(') {
                cnt++;
            } else if (i == ')') {
                cnt--;
            } else {
                cnt2++;
            }
        }
        if (abs(cnt) == cnt2) {
            cout << "Yes\n";
            return;
        }
    }
    if (count(s.begin(), s.end(), '?') > 92) {
        cout << "No\n";
        return;
    }
    int         padding = s.length();
    vector<int> dp1(s.length() * 2 + 1);  // 当(-)为i时，有多少种可能性？
    vector<int> dp2(s.length() * 2 + 1);
    dp1[padding] = 1;
    int no       = padding;
    int ab       = 0;
    for (char iter : s) {
        if (iter == '(') {
            no++;
            for (int j = max(no - ab, padding + 1); j <= no + ab; j++) {
                dp2[j] += dp1[j - 1];
            }
        } else if (iter == ')') {
            no--;
            for (int j = max(no - ab, padding); j <= no + ab; j++) {
                dp2[j] += dp1[j + 1];
            }
        } else {
            ab++;
            for (int j = max(no - ab, padding); j <= no + ab; j++) {
                dp2[j] += dp1[j - 1];
                dp2[j] += dp1[j + 1];
            }
        }
        swap(dp1, dp2);
        dp2.assign(s.length() * 2 + 1, 0);
    }
    cout << (dp1[padding] == 1 ? "Yes" : "No") << '\n';
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
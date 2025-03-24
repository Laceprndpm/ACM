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
    int cnt  = 0;
    int cnt2 = 0;
    s[0]     = '(';
    for (char i : s) {
        if (i == '(') {
            cnt++;
        } else if (i == ')') {
            cnt--;
            if (cnt < 0) {
                cnt++;
                cnt2--;
            }
        } else {
            cnt2++;
        }
        if (cnt == 0 && cnt2 == 1) {
            cnt  = 1;
            cnt2 = 0;
        }
    }
    cout << (cnt == cnt2 ? "YES\n" : "NO\n");
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
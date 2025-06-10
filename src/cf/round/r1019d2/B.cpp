#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    bool on1 = false;
    int  ans = 0;
    int  t   = 0;
    for (char c : s) {
        if (c == '0') {
            if (on1) {
                on1 = false;
                ans++, t++;
            }
            ans++;
        } else {
            if (!on1) {
                on1 = true;
                ans++, t++;
            }
            ans++;
        }
    }
    if (t >= 3) {
        ans -= 2;
    } else if (t >= 2) {
        ans--;
    }
    cout << ans << '\n';
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
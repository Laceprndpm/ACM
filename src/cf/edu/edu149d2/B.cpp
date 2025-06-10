#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int    n;
    string s;
    cin >> n;
    cin >> s;
    char last   = s[0];
    int  cnt    = 1;
    int  maxCnt = 1;
    for (int i = 1; i < n; i++) {
        char cur = s[i];
        if (last == cur) {
            cnt++;
            maxCnt = max(maxCnt, cnt);
        } else {
            last = cur;
            cnt  = 1;
        }
    }
    cout << maxCnt + 1 << '\n';
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
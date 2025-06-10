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
    i64 cnt_ = 0, cntOther = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '_') {
            cnt_++;
        } else {
            cntOther++;
        }
    }
    i64 cnt_1 = cntOther / 2;
    cntOther -= cnt_1;
    i64 ans = cnt_ * cntOther * cnt_1;
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
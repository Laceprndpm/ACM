#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    string s;
    cin >> s;
    int  n    = s.length();
    char last = '0';
    for (int i = 0; i < n; i++) {
        char& cur = s[i];
        if (cur == '?') {
            cur = last;
        } else {
            last = cur;
        }
    }
    cout << s << '\n';
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
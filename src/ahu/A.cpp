#include <iostream>
#include <utility>
#include <vector>
#define REMOVE_ME
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string s;
    cin >> s;
    vector<pair<i64, i64>> dp(s.length());
    i64                    ans = 0;
    vector<i64>            last(26, -1);
    for (i64 i = 0; i < s.length(); i++) {
        dp[i].first      = last[s[i] - 'a'];
        last[s[i] - 'a'] = i;
    }
    last.assign(26, s.length());
    for (i64 i = s.length() - 1; i >= 0; i--) {
        dp[i].second     = last[s[i] - 'a'];
        last[s[i] - 'a'] = i;
    }
    for (i64 i = 0; i < s.length(); i++) {
        ans += (i - dp[i].first) * (dp[i].second - i);
    }
    // ans -= s.length();
    cout << ans;
    return 0;
}
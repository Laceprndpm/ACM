#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    string s, t;
    cin >> s >> t;
    i64            lens = sz(s);
    i64            lent = sz(t);
    vector<string> dp(lent + 1);
    for (int i = 0; i < lens; i++) {
        for (int j = lent - 1; j >= 0; j--) {
            auto tmp = (j - 1 < 0 ? "" : dp[j - 1]) + (t[j] == s[i] ? string(1, t[j]) : "");
            dp[j]    = sz(dp[j]) < sz(tmp) ? tmp : dp[j];
        }
        for (int j = 1; j < lent; j++) {
            dp[j] = sz(dp[j]) < sz(dp[j - 1]) ? dp[j - 1] : dp[j];
        }
    }
    cout << dp[lent - 1];
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
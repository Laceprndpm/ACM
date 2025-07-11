#include <array>
#include <iostream>
#include <string>
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
constexpr i64 MOD = 1e9 + 7;

void solve()
{
    vector<i64> mi(19);
    mi[0] = 1;
    for (int i = 1; i <= 18; i++) {
        mi[i] = mi[i - 1] * 10ll;
    }
    vector<i64> dp(19);
    for (int i = 0; i < 18; i++) {
        dp[i + 1] = dp[i] * 10 + mi[i];
    }
    // 和P2602没区别
    auto func = [&](string s) -> array<i64, 10> {
        int            Len = s.length();
        array<i64, 10> cnt{0};
        i64            tmp = stoll(s);
        for (int i = 0; i < Len; i++) {
            int cur_len = Len - i;
            for (int j = 0; j < 10; j++) {
                cnt[j] += (s[i] - '0') * dp[cur_len - 1];
            }
            for (int j = 0; j < s[i] - '0'; j++) {
                cnt[j] += mi[cur_len - 1];
            }
            tmp -= 1ll * (s[i] - '0') * mi[cur_len - 1];
            cnt[s[i] - '0'] += tmp + 1;
            cnt[0] -= mi[cur_len - 1];
            for (int i = 0; i < 10; i++) {
                cnt[i] %= MOD;
            }
        }
        return cnt;
    };
    string L, R;
    cin >> L >> R;
    auto res1 = func(L), res2 = func(R);
    for (int i = 0; i < 10; i++) {
        res2[i] -= res1[i];
    }
    i64 ans = 0;
    for (int i = 0; i < 10; i++) {
        ans += res2[i] * 1ll * i;
        ans %= MOD;
    }
    for (char c : L) {
        ans += c - '0';
    }
    ans += MOD;
    ans %= MOD;
    cout << ans << '\n';
}

signed main(signed argc, char** argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
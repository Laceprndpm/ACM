#include <algorithm>
#include <iostream>
#include <string>
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

i64 qpow(i64 n, i64 q)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
        }
        n *= n;
        q >>= 1;
    }
    return ans;
}

void solve()
{
    string l, r;
    cin >> l >> r;
    int ln = stoi(l), rn = stoi(r);
    int len = sz(l);
    int dp1 = INF, dp2 = INF, dp3 = INF, dp4 = 0;
    for (int i = 0; i < len; i++) {
        if (l[i] == r[i]) {
            dp4 += 2;
            // dp2 += 2;
            // dp3 += 2;
            dp1 = min({dp2, dp3, dp1});
        } else if (l[i] + 1 == r[i]) {
            dp1 = min({dp2, dp3, dp1});
            dp2 = min(dp2, dp4) + 1;
            dp3 = min(dp3, dp4) + 1;
            dp4 = INF;
        } else if (l[i] + 1 == r[i] + 10) {
            dp2 = min(dp2, dp4) + 1;
            dp3 = min(dp3, dp4) + 1;
            dp4 = INF;
        } else {
            dp1 = min({dp1, dp2, dp3, dp4});
            dp2 = dp3 = dp4 = INF;
        }
    }
    // int i = 0;
    // while (i < len && l[i] == r[i]) {
    //     i++;
    //     dp4 += 2;
    // }
    // dp2 = dp3 = dp4;
    // while (i < len && ln + qpow(10, len - i) == rn) {
    //     i++;
    //     dp2++;
    // }
    cout << min({dp1, dp2, dp3, dp4}) << '\n';
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
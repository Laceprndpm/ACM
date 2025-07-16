#include <cmath>
#include <iostream>
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
constexpr i64 MOD = 998244353;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 已知b
    // 令a > b,则c!=a和b
    // 哦，a != kb，难道说分块就妙了？
    //
    //
    i64 n;
    cin >> n;
    i64 ans = 0;
    i64 i;
    for (i = 2; i < sqrt(n); i++) {
        ans += n - i + 1;
        ans -= n / i;
        ans %= MOD;
    }
    while (i < n) {
        i64 val = n / i;
        i64 nxt = n / val + 1;
        nxt     = min(nxt, n + 1);
        ans += (nxt - i) % MOD * ((n + 1) % MOD);
        ans %= MOD;
        ans -= (nxt + i - 1) % MOD * ((nxt - i) % MOD) % MOD * 499122177;
        ans += MOD;
        ans %= MOD;
        ans -= val * (nxt - i);
        ans += MOD;
        ans %= MOD;
        i = nxt;
    }
    ans += MOD;
    ans %= MOD;
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
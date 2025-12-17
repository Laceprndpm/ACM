#include <cstring>
#include <iostream>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

void solve()
{
    int n, k;
    cin >> n >> k;
    int dp[40][40][2];
    memset(dp, 0xc0, sizeof dp);
    dp[0][0][0] = 0;
    auto relax  = [](int& x, int y) { x = max(x, y); };
    for (int i = 0; i <= 30; i++) {
        for (int j = 0; j <= 30; j++) {
            for (int k = 0; k < 2; k++) {
                int curpos = (n >> i & 1) ^ k;                      // 当前位置
                int addone = ((n >> i & 1) && k);                   // 当前位置是否进位
                relax(dp[i + 1][j][addone], dp[i][j][k] + addone);  // 不管
                if (curpos == 1) {                                  // 仅当当前位置为1才考虑+1
                    relax(dp[i + 1][j + 1][1], dp[i][j][k] + 1);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= min(31, k); i++) {
        for (int ik = 0; ik < 2; ik++) {
            ans = max(ans, dp[31][i][ik] + k - i);
        }
    }
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
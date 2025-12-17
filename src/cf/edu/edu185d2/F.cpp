#include <array>
#include <iostream>
#include <vector>
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
    // [12][1 << 12]
    // 每次merge复杂度为(12**2) * log(n) * q
    constexpr int B = (1 << 12);
    int           n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int q;
    cin >> q;
    vector<vector<array<int, 3>>> querys(n + 1);
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        querys[r].pb({l, x, i});
    }
    array<array<int, 13>, B> dp;
    for (auto& v : dp) {
        for (auto& vv : v) {
            vv = 0;
        }
    }
    vector<int> ans(q);
    // dp[i][j] 达到 i 时，用了 j 个数，则左端点位于
    for (int i = 1; i <= n; i++) {
        int curval = arr[i];
        for (int v = 0; v < B; v++) {
            for (int j = 12; j >= 2; j--) {
                dp[v][j] = max(dp[v][j], dp[v ^ curval][j - 1]);
            }
        }
        dp[curval][1] = i;
        for (auto [l, x, id] : querys[i]) {
            int curans = 0;
            for (int j = 1; j <= 12; j++) {
                if (dp[x][j] >= l) {
                    curans = j;
                    break;
                }
            }
            ans[id] = curans;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << " \n"[i == q - 1];
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}

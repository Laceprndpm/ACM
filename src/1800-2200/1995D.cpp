#include <array>
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

void solve()
{
    int n, c, k;
    cin >> n >> c >> k;
    string s;
    cin >> s;
    vector<array<int, 18>> sPre(1, {0});
    for (int i = 0; i < n; i++) {
        auto bak = sPre.bk;
        bak[s[i] - 'A']++;
        sPre.eb(bak);
    }
    int         FULL = (1 << c) - 1;
    vector<int> bad(1 << c);
    for (int i = 0; i <= n - k; i++) {
        int num = 0;
        for (int j = 0; j < c; j++) {
            if (sPre[i][j] != sPre[i + k][j]) {
                num |= 1 << j;
            }
        }
        bad[FULL ^ num] = 1;
    }
    bad[FULL ^ (1 << (s.back() - 'A'))] = 1;
    for (int i = FULL - 1; i >= 0; i--) {
        for (int j = 0; j < c; j++) {
            bad[i] |= bad[i | 1 << j];
        }
    }
    int ans = c;
    for (int i = 0; i < FULL; i++) {
        if (!bad[i]) {
            ans = min(ans, __builtin_popcount(i));
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
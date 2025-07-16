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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // b ** 2 - a ** 2 = (b - a) * (a + b)
    // a + b % 2 == 0
    // b - a % 2 == 0
    // 12 = 2 * 6
    // 16 = 2 * 8 5 - 3 * (5 + 3)
    //
    // 7 + 5
    //
    //
    int t;
    cin >> t;
    while (t--) {
        i64 a, b;
        cin >> a >> b;
        i64 val       = abs(a * a - b * b);
        i64 all_odds  = val / 2ll - 1ll;
        i64 all_evens = max((val - 1ll) / 4ll - 1, 0ll);
        i64 ans       = all_evens + all_odds + 1;
        cout << ans << '\n';
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
#include <iostream>
#include <ranges>
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
    i64 n, l, r, k;
    cin >> n >> l >> r >> k;
    if (n % 2) {
        cout << l << '\n';
        return;
    }
    if (n == 2) {
        cout << "-1\n";
        return;
    }
    i64 bak = 0;
    int i;
    for (i = 61; i >= 0; i--) {
        if (l >> i & 1) {
            bak |= 1ll << (i + 1);
            break;
        }
    }
    if (bak > r) {
        cout << -1 << '\n';
        return;
    }
    if (k + 1 == n || k == n) {
        cout << bak << '\n';
    } else {
        cout << l << '\n';
    }
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
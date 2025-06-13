#include <algorithm>
#include <iostream>
#include <numeric>
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
    int n;
    cin >> n;
    // vector<vector<int>> bd(n + 1, vector<int>(n + 1));
    // for (int i = 1; i <= n; i++) {
    //     iota(all(bd[i]), 0);
    // }
    cout << 2 * n - 1 << '\n';
    cout << "1 1 " << n << '\n';
    for (int i = 2; i <= n; i++) {
        // reverse(bd[i].begin() + 1, bd[i].begin() + i);
        // reverse(bd[i].begin() + i, bd[i].end());
        cout << i << ' ' << 1 << ' ' << i - 1 << '\n';
        cout << i << ' ' << i << ' ' << n << '\n';
    }
    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         cout << bd[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
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
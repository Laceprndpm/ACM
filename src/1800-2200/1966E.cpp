#include <algorithm>
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

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int idx    = 0;
    int direct = 1;
    int mn = 0, mx = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            direct = direct * -1;
        } else {
            idx += direct;
            mn = min(idx, mn);
            mx = max(idx, mx);
        }
    }
    // xxxx1
    // xx101
    // xx101
    // xxx01
    // xxx01
    // xxxx1

    cout << mx - mn + 1 << '\n';
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
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
    int w, h, a, b;
    int x1, y1, x2, y2;
    cin >> w >> h >> a >> b;
    cin >> x1 >> y1 >> x2 >> y2;
    if (x2 == x1) {
        if ((y2 - y1) % b == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else if (y2 == y1) {
        if ((x2 - x1) % a == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    } else if ((x2 - x1) % a == 0 || (y2 - y1) % b == 0) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
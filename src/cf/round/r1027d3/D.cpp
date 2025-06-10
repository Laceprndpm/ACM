#include <algorithm>
#include <fstream>
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

constexpr i64 INF = 1e18;

void solve()
{
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    int  mnX = min_element(all(x)) - bg(x), mxX = max_element(all(x)) - bg(x);
    int  mnY = min_element(all(y)) - bg(y), mxY = max_element(all(y)) - bg(y);
    auto mn = [&](auto x, int v) {
        // if (v == 0) {
        //     return *min_element(x.begin() + v + 1, x.end());
        // }
        // if (v == sz(x) - 1) {
        //     return *min_element(x.begin(), x.begin() + v);
        // }
        // int mnx = min(*min_element(x.begin(), x.begin() + v), *min_element(x.begin() + v + 1, x.end()));
        // return mnx;
        for (int i = 0; i < sz(x); i++) {
            
        }
    };
    auto mx = [&](auto x, int v) {
        if (v == 0) {
            return *max_element(x.begin() + v + 1, x.end());
        }
        if (v == sz(x) - 1) {
            return *max_element(x.begin(), x.begin() + v);
        }
        int mxx = max(*max_element(x.begin(), x.begin() + v), *max_element(x.begin() + v + 1, x.end()));
        return mxx;
    };
    auto check = [&](int v) -> i64 {
        int mnx = mn(x, v);
        int mxx = mx(x, v);
        int mny = mn(y, v);
        int mxy = mx(y, v);
        i64 h   = mxx - mnx + 1;
        i64 w   = mxy - mny + 1;
        i64 s   = h * w;
        if (s < n) {
            s += min(h, w);
        }
        return s;
    };
    int candidate[] = {mnX, mxX, mnY, mxY};
    i64 ans         = INF;
    for (int i : candidate) {
        ans = min(check(i), ans);
    }
    cout << ans << '\n';
    // sort(all(x));
    // sort(all(y));
    // int x_l = x[0], x_r = x[n - 1];
    // int x_ll = x[1], x_rr = x[n - 2];
    // int y_l = y[0], y_r = y[n - 1];
    // int y_ll = y[1], y_rr = y[n - 2];
    // if (x_ll != x_l) {

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
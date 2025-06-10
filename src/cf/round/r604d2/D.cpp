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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // first, obsly, there will be some more 1, 2
    // that is unused
    // if no more,then impossible
    // I can repeat them when gap two seg
    // then JUST put one at the end!
    // wait, if more one?
    // maybe Impossible, guess
    // ez
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    string ans = "";
    // if (a + b + c + d == 1) {
    //     if (a == 1) {
    //         ans = "0";
    //         a   = 0;
    //     }
    //     if (b == 1) {
    //         ans = "1";
    //         b   = 0;
    //     }
    //     if (c == 1) {
    //         ans = "2";
    //         c   = 0;
    //     }
    //     if (d == 1) {
    //         ans = "3";
    //         d   = 0;
    //     }
    // } else
    if (((a + b) == 0)) {
        if (d != 0) {
            int mn = min(c, d);
            for (int i = 0; i < mn; i++) {
                ans += "23";
            }
            c -= mn, d -= mn;
            if (d == 1) {
                ans = "3" + ans;
                d   = 0;
            }
        }
        if (c == 1) {
            ans = ans + "2";
            c   = 0;
        }
    } else if ((c + d) == 0) {
        if (a != 0) {
            int mn = min(a, b);
            for (int i = 0; i < mn; i++) {
                ans += "10";
            }
            a -= mn, b -= mn;
            if (a == 1) {
                ans = "0" + ans;
                a   = 0;
            }
        }
        if (b == 1) {
            ans = ans + "1";
            b   = 0;
        }
    } else {
        if (a > b || c < d) {
            cout << "NO\n";
            return 0;
        }
        string left = "";
        for (int i = 0; i < a; i++) {
            left += "01";
        }
        string right = "";
        for (int i = 0; i < d; i++) {
            right += "23";
        }
        b -= a, c -= d;
        a = 0, d = 0;
        int    mn  = min(b, c);
        string mid = "";
        for (int i = 0; i < mn; i++) {
            mid += "21";
        }
        ans = left + mid + right;
        b -= mn, c -= mn;
        if (b == 1) {
            b   = 0;
            ans = "1" + ans;
        }
        if (c == 1) {
            c   = 0;
            ans = ans + "2";
        }
    }
    if (a == 0 && c == 0 && b == 0 && d == 0) {
        cout << "YES\n";
        for (char i : ans) {
            cout << i << ' ';
        }
        return 0;
    }
    cout << "NO\n";
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
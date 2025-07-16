#include <iostream>
#include <string>
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
    int a, b, k;
    cin >> b >> a >> k;
    a--;
    int max1num = b + (a - 1);
    if (k == 0) {
        cout << "Yes\n";
        cout << "1" + string(a, '1') + string(b, '0') << '\n';
        cout << "1" + string(a, '1') + string(b, '0') << '\n';
        return 0;
    }
    if (k > max1num || ((a == 0 || b == 0) && k != 0)) {
        cout << "No\n";
        return 0;
    }
    string x = "1", y = "1";
    while (b + (a - 1) > k) {
        if (b > 1) {
            x += "0";
            y += "0";
            b--;
        } else {
            x += "1";
            y += "1";
            a--;
        }
    }
    x += string(a, '1') + string(b, '0');
    y += string(1, '0') + string(a - 1, '1') + string(b - 1, '0') + string(1, '1');
    cout << "Yes\n";
    cout << x << '\n' << y << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
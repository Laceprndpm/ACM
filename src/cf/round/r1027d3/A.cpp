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

void solve()
{
    int s;
    cin >> s;
    // for (int i = 1; i < 3; i++) {
    //     string a(s.begin(), s.begin() + i);
    //     string b(s.begin() + i, s.begin() + 4);
    //     if ((stoi(a) + stoi(b)) * (stoi(a) + stoi(b)) == stoi(s)) {
    //         cout << stoi(a) << ' ' << stoi(b) << '\n';
    //         return;
    //     }
    // }
    for (int a = 0; a <= 100; a++) {
        for (int b = 0; b <= 100; b++) {
            if ((a + b) * (a + b) == s) {
                cout << a << ' ' << b << '\n';
                return;
            }
        }
    }
    cout << -1 << '\n';
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
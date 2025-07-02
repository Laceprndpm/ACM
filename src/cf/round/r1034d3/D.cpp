#include <iostream>
#include <set>
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
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0 + k; i < n; i++) {
        if (s[i] == '1') {
            cnt++;
            s[i] = '0';
        }
    }
    for (int i = 0; i < n - k; i++) {
        if (s[i] == '1') {
            cnt++;
            s[i] = '0';
        }
    }
    if (cnt <= k || 2 * k > n) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
    }
}

// k * 2 <= n
//
// xxx0xxx
// 1111000
//
// k * 2 > n
// 
// 000 1 000
// 111 1 111
// n = 7
// k = 4
// 000 1 000
// 001 1 100
//
// 11111111
// 10000000
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
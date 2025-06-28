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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    iota(all(arr), 1);
    int stkid = 0;
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int p, x;
            cin >> p >> x;
            p--;
            p += stkid;
            p %= n;
            arr[p] = x;
        } else if (cmd == 2) {
            int p;
            cin >> p;
            p--;
            p += stkid;
            p %= n;
            cout << arr[p] << '\n';
        } else {
            int k;
            cin >> k;
            stkid += k;
            stkid %= n;
        }
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
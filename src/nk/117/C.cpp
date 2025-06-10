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
#define int long long
signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 对于r - l 很大的情况，比如含有质数，然后我就可以全取偶数，剩下的组一队，可以保证<=1
    // 如果只要一个数，那肯定不行
    // 两个数，如果其中一个是1，则可以
    // 三个数，则可以相邻两个数gcd==1，然后剩下的自己组队
    // n % 2==1, n + 2和n是不是一定互质？True
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (r == l) {
            cout << "-1\n";
            continue;
        }
        if (r - l == 1) {
            if (l == 1) {
                cout << 0 << '\n';
            } else {
                cout << "-1\n";
            }
            continue;
        }
        if ((r - l + 1) % 2 == 0) {
            cout << 0 << '\n';
        } else {
            cout << 1 << '\n';
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
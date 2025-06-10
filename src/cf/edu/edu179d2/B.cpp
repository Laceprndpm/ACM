#include <algorithm>
#include <array>
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

constexpr int INF = 1e9;

vector<int> fib(15);

void solve()
{
    int n, m;
    cin >> n >> m;
    int           ch = fib[n], cw = fib[n - 1] + fib[n];
    array<int, 3> arr;
    auto          single_shoot = [&]() {
        sor(arr);
        do {
            if ((arr[0] >= ch) && (arr[1] >= ch) && (arr[2] >= cw)) {
                cout << 1;
                return;
            }
        } while (next_permutation(all(arr)));
        cout << 0;
        return;
    };
    for (int i = 0; i < m; i++) {
        int w, l, h;
        cin >> w >> l >> h;
        arr = {w, l, h};
        single_shoot();
    }
    cout << '\n';
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
    fib[1] = 1;
    fib[2] = 2;
    for (int i = 3; i < 15; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
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
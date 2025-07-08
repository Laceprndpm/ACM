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

void solve()
{
    // a(i+1) / ai
    // ai *= x后
    // 现在要让ai / x后，整除
    //
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (i64& i : arr) {
        cin >> i;
    }
    vector<i64> fa;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i + 1] % arr[i]) {
            fa.eb(arr[i] / gcd(arr[i], arr[i + 1]));
        }
    }
    if (fa.empty()) {
        cout << "123\n";
        return;
    }
    i64 cur = fa[0];
    for (int i = 0; i < sz(fa); i++) {
        cur = (cur * fa[i]) / gcd(cur, fa[i]);
    }
    cout << cur << '\n';
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
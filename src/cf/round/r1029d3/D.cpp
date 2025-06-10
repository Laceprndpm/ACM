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

tuple<i64, i64, i64> exgcd(i64 a, i64 b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {1, 0, a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    i64 x = ly;
    i64 y = lx - ly * (a / b);
    return {x, y, r};
}

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    int x = (arr[n] * 2 - arr[n - 1]) / (n + 1);
    // (arr[n] - x * n) * 2 = (arr[n - 1] - x * (n - 1))
    //   arr[n] * 2 - 2 * x * n = arr[n - 1] - x * (n - 1)
    // arr[n] * 2 - arr[n - 1]  = n * x + x
    int ok = 1;
    if (x < 0) ok = 0;
    for (i64 i = n; i >= 1; i--) {
        arr[i] -= i * x;
        if (arr[i] != (n - i + 1) * arr[n] || arr[i] < 0) {
            ok = 0;
        }
    }
    if (ok) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
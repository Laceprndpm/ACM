#include <algorithm>
#include <iostream>
#include <utility>
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
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 ans = 0;
    for (int aI = 0; aI < n; aI++) {
        for (int bI = aI + 1; bI < n; bI++) {
            const auto [a, b] = pair<int, int>{arr[aI], arr[bI]};
            const int cMax    = a + b - 1;
            const int cMin    = arr.back() - a - b + 1;
            if (cMax < cMin) continue;
            int num = upper_bound(bg(arr) + bI + 1, arr.end(), cMax) - lower_bound(bg(arr) + bI + 1, arr.end(), cMin);
            ans += num;
        }
    }
    cout << ans << '\n';
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
    // 设最大元素个数为2，可以选择这两个
    //
    // 胜利情况：a,b,c为红，d为蓝，且a + b + c > d
    // a, b, c < d
    // 或者已知我选择了a,b，我选择一个怎样的c可以保证不输？
    // c<a+b
    // a+b+c > max
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
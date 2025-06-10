#include <algorithm>
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

// d1A / d2C
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& x : arr) {
        cin >> x;
    }
    int res = arr[0];
    for (int i = 1; i < n; i++) {
        res = gcd(res, arr[i]);
    }
    int cnt = count(all(arr), res);
    if (cnt) {
        cout << n - cnt << '\n';
        return;
    }
    vector<int> min_op_times(5050, INF);
    for (int i = 0; i < n; i++) {
        min_op_times[arr[i]] = 0;
        for (int j = 1; j <= 5000; j++) {
            min_op_times[gcd(j, arr[i])] = min(min_op_times[j] + 1, min_op_times[gcd(j, arr[i])]);
        }
    }
    cout << min_op_times[res] + n - 1 << '\n';
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
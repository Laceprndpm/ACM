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

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<array<i64, 3>> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }
    sort(all(arr), [&](const auto& t, const auto& f) {
        return t[0] + t[1] < f[0] + f[1];
    });
    vector<i64> dp(20000 + 50);
    for (int i = 0; i < n; i++) {
        for (int j = arr[i][1]; j >= 0; j--) {
            dp[j + arr[i][0]] = max(dp[j + arr[i][0]], dp[j] + arr[i][2]);
        }
    }
    cout << *max_element(all(dp), [&](auto x, auto y) {
        return x < y;
    });
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
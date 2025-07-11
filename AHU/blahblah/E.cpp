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
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<i64> dp(456700);
    vector<i64> ndp = dp;
    while (true) {
        bool flag = 1;
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                flag = 0;
            }
        }
        if (flag) {
            for (int i = 0; i < n; i++) {
                arr[i] /= 2;
            }
        } else {
            break;
        }
    }
    dp[arr[0] + 200000] = 1;
    dp[200000 - arr[0]] = 1;
    for (int i = 1; i < n; i++) {
        fill(all(ndp), 0);
        for (int j = 0; j <= 400000; j++) {
            if (dp[j]) {
                ndp[j - arr[i]] = 1;
                ndp[j + arr[i]] = 1;
            }
        }
        swap(dp, ndp);
    }
    if (dp[200000]) {
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2) {
                cout << 1 << '\n';
                cout << i + 1 << '\n';
                break;
            }
        }
    } else {
        cout << 0 << '\n';
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
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
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
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<i64> brr(1, 0);
    for (i64& i : arr) {
        brr.eb(brr.bk + i);
    }
    i64 ans = 0;
    i64 s   = accumulate(all(arr), 0ll);
    if (s % 2 || s - 2ll * *max_element(all(arr)) < 0) {
        cout << -1 << '\n';
        return;
    }
    auto it = lower_bound(all(arr), 0ll);
    
    // while (true) {
    //     ans++;
    //     i64  sum    = brr[r] - brr[l];
    //     auto iter1  = lower_bound(all(brr), (sum + 1) / 2 + brr[l]);  // *iter - brr[l] >= sum / 2
    //     auto iter2  = prev(iter1);
    //     i64  small1 = sum - *iter1 - brr[l];
    //     i64  small2 = *iter2 - brr[l];
    //     if (sum - 2 * max(small1, small2) <= repair) {
    //         break;
    //     }
    //     if (small1 > small2) {
    //         repair += small1;
    //         r = iter1 - bg(brr);
    //     } else {
    //         repair += small2;
    //         l = iter2 - bg(brr);
    //     }
    // }
    cout << ans << '\n';
    // auto dfs = [&](this auto&& dfs, vector<i64> arr, i64 repair) {
    //     i64 sum = brr.bk;
    //     lower_bound()
    // };
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
    // 2 ** 17 == 131072
    //      5e4 == 50000
    // 假如我取前一半小的非负数，是不是一定可以被后一半大的齐平？
    //
    // 7 7 7 7 20
    // 1 1 2 2
    // 4 6
    //
    // 28 35 35
    // 1 2 3
    // 1 2
    // 5 3 | 1 5
    //   3 | 1 2
    // 5 0 | 0 3
    //
    // 1 1 2 4 8 16
    // 1 3 9 9
    // 0 0 8 8
    // 1 2 3 100 200 300 1000 2000 3000
    //
    // 1 1 2 2 4 4 8 16
    //
    // 22
    //
    //
    // 38
    //
    //
    // 4 ** 17 == 17179869184
    //    1e12 == 1000000000000
    // 8 ** 17 == 2251799813685248
    //
    // 只要偶数应该就可以吧？
    //
    // 1 99999
    // No
    //
    // 1 3 2
    // 1 1   op
    // 0 2 2
    // 0 0 0
    // 5 2 5
    // 1 1   op
    // 4 1 5
    // 4 1 5 op
    // 0 0 0
    // 也许我应该找到某个地方，其中左右不平衡，但是经过最少次数，就可以平衡左右
    // 只要2 * max <= sum且偶数就可行，是否意味着什么
    // 3 5 7 9 22
    //
    // 3 8 15 24 46 prefix
    //
    // 1 1 op
    //
    // 2 4 7 9 22
    // 0 0 0 0 0
    //
    //
    // 3 5 7 11 13 17  1e9 + 13
    // 3 8 15 26 39 56 1e9 + 63 2e9 + 76
    //
    // 3 17 13 11 7  5  5  7
    // 3 20 33 44 51 56 61 68
    //
    // 4 15 13
    // 4 19 32
    // 3 3    op
    // 1 12 13
    //
    //
    //
    // 如果我dp，可以获得这一块中，在单次操作下，总和可以减少x，这是连续的
    //
    //
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
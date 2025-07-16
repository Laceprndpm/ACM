#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
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

constexpr i64 INF = 1e18;

i64 log22(u64 x)
{
    if (x == 0) return 0;
    return (64 - __builtin_clzll(x - 1ull));
}

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr) {
        cin >> i;
    }
    vector<i64> prefix(1);
    for (i64 i : arr) {
        prefix.pb(prefix.bk + i);
    }
    vector<vector<vector<pair<i64, i64>>>> dp(n, vector<vector<pair<i64, i64>>>(n));
    for (int l = 0; l < n; l++) {
        dp[l][l].pb({0, 0});
    }

    for (int delta = 1; delta < n; delta++) {
        for (int l = 0; l + delta < n; l++) {
            int                    r = l + delta;
            vector<pair<i64, i64>> mono_queue;
            // vector<pair<i64, i64>> buffer;
            // for (int mid = l; mid + 1 <= r; mid++) {
            //     i64  left          = prefix[mid + 1] - prefix[l];
            //     i64  right         = prefix[r + 1] - prefix[mid + 1];
            //     i64  cur_imbalance = abs((left) - (right));
            //     auto it1           = upper_bound(all(dp[l][mid]), pair<i64, i64>{cur_imbalance, INF});
            //     auto it2           = upper_bound(all(dp[mid + 1][r]), pair<i64, i64>{cur_imbalance, INF});
            //     if (it1 == dp[l][mid].begin() || it2 == dp[mid + 1][r].begin()) continue;
            //     it1 = prev(it1), it2 = prev(it2);
            //     buffer.pb({cur_imbalance, it1->second + it2->second + std::min(left, right) * log22(left + right)});
            // }
            // sor(buffer);
            // for (auto i : buffer) {
            //     if (!mono_queue.empty() && mono_queue.bk.second <= i.second) {
            //         continue;
            //     }
            //     mono_queue.pb(i);
            // }

            //
            int idx_l = l, idx_r = r - 1;
            while (idx_l <= idx_r) {
                i64 l_left  = prefix[idx_l + 1] - prefix[l];
                i64 l_right = prefix[r + 1] - prefix[idx_l + 1];

                i64 r_left  = prefix[idx_r + 1] - prefix[l];
                i64 r_right = prefix[r + 1] - prefix[idx_r + 1];

                i64 l_imbalance = abs(l_left - l_right);
                i64 r_imbalance = abs(r_left - r_right);

                i64  choose        = (l_imbalance > r_imbalance) ? idx_l : idx_r;
                i64  cur_imbalance = (l_imbalance > r_imbalance) ? l_imbalance : r_imbalance;
                auto it1           = upper_bound(all(dp[l][choose]), pair<i64, i64>{cur_imbalance, INF});
                auto it2           = upper_bound(all(dp[choose + 1][r]), pair<i64, i64>{cur_imbalance, INF});
                if (l_imbalance > r_imbalance) {
                    idx_l++;
                } else {
                    idx_r--;
                }
                if (it1 == dp[l][choose].begin() || it2 == dp[choose + 1][r].begin()) continue;
                it1 = prev(it1), it2 = prev(it2);
                auto [left, right] =
                    (l_imbalance > r_imbalance) ? pair<i64, i64>{l_left, l_right} : pair<i64, i64>{r_left, r_right};
                i64 cost = it1->second + it2->second + std::min(left, right) * log22(left + right);
                while (!mono_queue.empty() && mono_queue.bk.second >= cost) {
                    mono_queue.pop_back();
                }
                mono_queue.pb({cur_imbalance, cost});
            }
            reverse(all(mono_queue));
            dp[l][r] = std::move(mono_queue);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        i64  left = prefix[i + 1], right = prefix[n] - prefix[i + 1];
        i64  cur_imbalance = abs(left - right);
        auto it1           = upper_bound(all(dp[0][i]), pair<i64, i64>{cur_imbalance, INF});
        auto it2           = upper_bound(all(dp[i + 1][n - 1]), pair<i64, i64>{cur_imbalance, INF});
        if (it1 == dp[0][i].begin() || it2 == dp[i + 1][n - 1].begin()) {
            cout << -1 << ' ';
            continue;
        }
        i64 ans = std::prev(it1)->second + std::prev(it2)->second + min(left, right) * log22(left + right);
        cout << ans << ' ';
    }
    cout << '\n';
}

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 首先肯定是区间dp
    // dp[l][r]
    // 我可以有多种取法来导致第一次的imbalance度不同，而cost也不同
    // 只要父亲大于两个儿子，就可以成功转移
    // 但是，很明显不可能用一个数组来存imbalance度，需要套map？
    // map<imbalance, cost>
    // 如果双指针判断imbalance,可以从imbalance大到小，此时就可以单调栈优化
    //
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
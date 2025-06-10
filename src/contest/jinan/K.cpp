#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, k;
    cin >> n >> k;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] -= i;
    }
    deque<i64>               maxDq;
    i64                      curCost = 0;
    i64                      i = 0, j = 0;
    i64                      ans = 1;
    multiset<i64, greater<>> left;
    multiset<i64>            right;
    i64                      mid;
    auto                     balance = [&](void) -> void {
        // 4 1 1 4
        //
        if (right.empty() && !left.empty()) {
            i64  temp = *left.begin();
            auto it   = left.lower_bound(temp);
            right.insert(temp);
            left.erase(it);
            curCost = 0;
            return;
        }
        if (left.size() < right.size() - 1) {
            i64  oldmid = *right.begin();
            auto it     = right.lower_bound(oldmid);
            right.erase(it);
            i64 newmid = *right.begin();
            i64 delta  = newmid - oldmid;
            curCost += (left.size() + 1) * delta;
            curCost -= (right.size()) * delta;

            left.insert(oldmid);
        } else if (left.size() > right.size()) {
            i64  newmid = *left.begin();
            auto it     = left.lower_bound(newmid);
            left.erase(it);
            i64 oldmid = *right.begin();
            i64 delta  = oldmid - newmid;
            curCost -= (left.size() + 1) * delta;
            curCost += (right.size()) * delta;

            right.insert(newmid);
        }
    };
    auto balanceL = [&](void) -> void {
        i64  newmid = *left.begin();
        auto it     = left.lower_bound(newmid);
        left.erase(it);
        i64 oldmid = *right.begin();
        i64 delta  = oldmid - newmid;
        curCost -= (left.size() + 1) * delta;
        curCost += (right.size()) * delta;

        right.insert(newmid);
    };
    for (; j < n; j++) {
        if (!right.empty()) {
            mid = *right.begin();
            if (arr[j] >= mid) {
                curCost += arr[j] - mid;
                right.insert(arr[j]);
            } else {
                curCost += mid - arr[j];
                left.insert(arr[j]);
            }
        } else {
            right.insert(arr[j]);
            curCost = 0;
        }
        balance();
        while (curCost > k) {
            mid = *right.begin();
            if (arr[i] < mid) {
                // mid = *right.begin();
                curCost -= abs(arr[i] - mid);
                auto it = left.lower_bound(arr[i]);
                left.erase(it);
            } else {
                balanceL();
                mid     = *right.begin();
                auto it = right.lower_bound(arr[i]);
                curCost -= abs(arr[i] - mid);
                right.erase(it);
            }
            i++;
            balance();
        }
        // i64 curMax = arr[maxDq.front()];
        // curCost += curMax - arr[j];
        // if (curMax < arr[j]) {
        //     curCost += (j - i + 1) * (arr[j] - curMax);
        //     while (maxDq.size() >= 1 && arr[maxDq.front()] <= arr[maxDq.back()]) {
        //         maxDq.pop_front();
        //     }
        // }
        // while (curCost > k) {
        //     i64 curMax = arr[maxDq.front()];            // 当前最大
        //     curCost -= curMax - arr[i];                 // 删除左端点
        //     i++;                                        // 先移动左端点
        //     if (!maxDq.empty() && maxDq.front() < i) {  // 是否可以掉落
        //         curCost -= arr[maxDq.front()] * (j - i + 1);
        //         maxDq.pop_front();
        //         curCost += arr[maxDq.front()] * (j - i + 1);
        //     }
        // }
        ans = max(j - i + 1, ans);
    }
    cout << ans << '\n';
}

signed main(int argc, char** argv)
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
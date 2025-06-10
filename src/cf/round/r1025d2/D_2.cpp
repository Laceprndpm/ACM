#include <algorithm>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e16;

void solve()
{
    i64 n, m, l;
    cin >> n >> m >> l;
    vector<i64> arr(l);
    for (int i = 0; i < l; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    i64 sum1 = accumulate(arr.begin(), arr.end(), 0ll);
    i64 sum2 = -1;
    for (int i = 0; i < l; i++) {
        if (arr[i] % 2 == 1) {  // 找到第一个奇数，与sum1奇偶不同的最大的数一定是sum1 - 第一个奇数
            sum2 = sum1 - arr[i];
            break;
        }
    }
    vector<vector<i64>> dis(2, vector<i64>(n + 1, INF));  // 初始化为无穷大
    vector<vector<int>> graph(n + 1);                     // 建图
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // 我是不是可以计算出到达每个点，的奇数最短路和偶数最短路，如果存在的话？
    deque<pair<int, int>> que;  // i, j分别为位置和距离
    que.push_back({1, 0});      // 加入起始点
    dis[0][1] = 0;
    while (!que.empty()) {
        auto [cur, d] = que.front();
        que.pop_front();
        for (int adj : graph[cur]) {
            if (dis[(d + 1) % 2][adj] <= d + 1) continue;  // 对于所有邻居，如果无法更新答案，说明回头了，且无意义的回头
            dis[(d + 1) % 2][adj] = d + 1;  // 否则更新答案
            que.push_back({adj, d + 1});    // 加入队列
        }
    }
    if (sum2 != -1) assert(sum1 % 2 != sum2 % 2);
    for (int i = 1; i <= n; i++) {
        if ((dis[sum1 % 2][i] <= sum1) || (sum2 != -1 && dis[sum2 % 2][i] <= sum2)) {
            cout << 1;
        } else {
            cout << 0;
        }
    }
    cout << '\n';
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
    // 很明显的，我可以反复横跳
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
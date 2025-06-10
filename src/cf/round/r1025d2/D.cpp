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
constexpr i64 INF = 1e1;

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<i64> arr(l);
    for (int i = 0; i < l; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    i64 sum1 = accumulate(arr.begin(), arr.end(), 0ll);
    i64 sum2 = -1;
    for (int i = 0; i < l; i++) {
        if (arr[i] % 2 == 1) {
            sum2 = sum1 - arr[i];
            break;
        }
    }
    vector<vector<i64>> dis(2, vector<i64>(n + 1, INF));
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    // 我是不是可以计算出到达每个点，的奇数最短路和偶数最短路，如果存在的话？
    deque<pair<int, int>> que;
    // vector<int>           vis(n + 1);
    que.push_back({1, 0});
    dis[0][1] = 0;
    dis[1][1] = 0;
    while (!que.empty()) {
        auto [cur, d] = que.front();
        que.pop_front();
        for (int adj : graph[cur]) {
            assert(adj);
            if (dis[(d + 1) % 2][adj] <= d + 1) continue;
            dis[(d + 1) % 2][adj] = d + 1;
            que.push_back({adj, d + 1});
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
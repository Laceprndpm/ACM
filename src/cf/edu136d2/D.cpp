#include <algorithm>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>         father(n + 1);
    vector<int>         depth(n + 1);
    vector<int>         cntDepth(n + 1);
    vector<vector<int>> graph(n + 1);
    int                 depthest = 0;
    for (int i = 2; i <= n; i++) {
        cin >> father[i];
        graph[father[i]].emplace_back(i);
        depth[i] = depth[father[i]] + 1;
        cntDepth[depth[i]]++;
        depthest = max(depth[i], depthest);
    }
    // 不能简单将最深的点移到
    // 根节点，因为会出现菊花树，此时移动根节点有更高性价比
    // 我赌二分
    //
    // 设最深为x，则深度等于x+1才可接到1处，且每个都会被移动一次
    // 2 * x + 1也会被移动一次
    //
    //
    function<pair<int, int>(int root, int x)> mydfs = [&](int root, int x) {
        int hereCut = 0;
        int depth   = 1;
        for (int i : graph[root]) {
            if (i == father[root]) continue;
            auto [adjCut, adjDepth] = mydfs(i, x);
            hereCut += adjCut;
            if (adjDepth <= x || root == 1) {
                depth = max(depth, adjDepth);
            } else {
                hereCut++;
            }
        }
        return pair<int, int>{hereCut, depth + 1};
    };
    function<bool(int x)> check = [&](int x) {
        // 得要树上dp，设dp[i]为处理完该节点时，至少要value刀
        // 也许只需要一次DFS
        vector<int> dp(depthest + 1);
        auto [cnt, _] = mydfs(1, x);
        return cnt <= k;
    };
    int l = 1, r = depthest;
    while (l < r) {
        int mid = (r + l) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << '\n';
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
#include <algorithm>
#include <functional>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

tuple<int, int, int> dfs_D(const vector<vector<int>>& tree)
{
    vector<int>              d1(tree.size());
    int                      rt1  = 0;
    int                      rt2  = 0;
    function<void(int, int)> dfs1 = [&](int cur, int father) -> void {
        d1[cur] = d1[father] + 1;
        if (d1[cur] > d1[rt1]) rt1 = cur;
        for (int adj : tree[cur]) {
            if (adj == father) continue;
            dfs1(adj, cur);
        }
    };
    function<void(int, int)> dfs2 = [&](int cur, int father) -> void {
        d1[cur] = d1[father] + 1;
        if (d1[cur] > d1[rt2]) rt2 = cur;
        for (int adj : tree[cur]) {
            if (adj == father) continue;
            dfs2(adj, cur);
        }
    };
    dfs1(1, 0);
    d1.assign(d1.size(), 0);
    dfs2(rt1, 0);
    return {rt1, rt2, d1[rt2] - 1};
}

tuple<vector<int>, int> dfs_longest(const vector<vector<int>>& tree)

{
    vector<int>                   longest(tree.size(), -1);
    function<void(int, int, int)> dfs3 = [&](int cur, int father, int dist) -> void {
        longest[cur] = max(longest[cur], dist);
        for (int adj : tree[cur]) {
            if (adj == father) continue;
            dfs3(adj, cur, dist + 1);
        }
    };
    auto&& [rt1, rt2, D] = dfs_D(tree);
    dfs3(rt2, 0, 0);
    dfs3(rt1, 0, 0);
    return {longest, D};
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
    i64 n1, n2;
    cin >> n1;
    vector<vector<int>> tree1(n1 + 1);
    for (int i = 0; i < n1 - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree1[u].emplace_back(v);
        tree1[v].emplace_back(u);
    }
    cin >> n2;
    vector<vector<int>> tree2(n2 + 1);
    for (int i = 0; i < n2 - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree2[u].emplace_back(v);
        tree2[v].emplace_back(u);
    }
    auto&& [long1, D1] = dfs_longest(tree1);
    auto&& [long2, D2] = dfs_longest(tree2);
    i64 ans            = 0;
    sort(long1.begin() + 1, long1.end());
    sort(long2.begin() + 1, long2.end());
    vector<i64> prefix(long2.size() + 1);
    for (int i = 1; i <= n2; i++) {
        prefix[i + 1] = prefix[i] + long2[i];
    }
    int D = max(D1, D2);
    for (int i = 1; i <= n1; i++) {
        // ans += long1[i] * n2;
        int  r  = D - long1[i] - 1;
        auto it = lower_bound(long2.begin() + 1, long2.end(), r);
        ans += D * (it - long2.begin() - 1);
        ans += (long1[i] + 1) * (long2.end() - it);
        ans += prefix[n2 + 1] - prefix[it - long2.begin()];
    }

    cout << ans << '\n';
    return 0;
}

// function<void(int, int)> dfs1 = [&](int cur, int father) -> void {
//     d1[cur] = d1[father] + 1;
//     if (d1[cur] > d1[rt1]) rt1 = cur;
//     for (int adj : tree[cur]) {
//         if (adj == father) continue;
//         dfs1(adj, cur);
//     }
// };
// function<void(int, int)> dfs2 = [&](int cur, int father) -> void {
//     d2[cur] = d2[father] + 1;
//     if (d2[cur] > d2[rt2]) rt2 = cur;
//     for (int adj : tree[cur]) {
//         if (adj == father) continue;
//         dfs2(adj, cur);
//     }
// };

// vector<int>             submlongest(tree.size(), -1);
// vector<int>             mainGo(tree.size(), 0);
// function<int(int, int)> dfs = [&](int u, int last) -> int {
//     if (longest[u] != -1) {
//         if (last != mainGo[u])
//             return longest[u];
//         else
//             return submlongest[u];
//     }
//     int sonMax    = 0;
//     int sonSubMax = 0;
//     int curGo     = 0;
//     for (int adj : tree[u]) {
//         if (adj == last) continue;
//         int cur = dfs(adj, u);
//         if (cur > sonMax) {
//             sonSubMax = sonMax;
//             sonMax    = cur;
//             curGo     = adj;
//         } else if (cur > sonSubMax) {
//             sonSubMax = cur;
//         }
//     }
//     // int ret = sonMax + 1;
//     // if (longest[u] == -1 && last != -2) {
//     //     int cur = dfs(last, u);
//     //     if (cur > sonMax) {
//     //         sonMax = cur;
//     //         curGo  = last;
//     //     } else if (cur == sonMax) {
//     //         curGo = -1;
//     //     }
//     // }
//     longest[u]     = sonMax + 1;
//     mainGo[u]      = curGo;
//     submlongest[u] = sonSubMax + 1;
//     if (last != mainGo[u])
//         return longest[u];
//     else
//         return submlongest[u];
// };
// for (int i = 1; i <= n; i++) {
//     longest[i] = dfs(i, -2);
// }

// function<void(int, int)> dfs = [&](int u, int last) -> void {
//     for (int i : tree[u]) {
//         if (i == last) continue;
//         dfs(i, u);
//         if (longest[i] + 1 > longest[u]) {
//             longest[u]   = longest[i] + 1;
//             maxlencnt[u] = 0;
//         } else if (longest[i] + 1 == longest[u]) {
//             maxlencnt[u]++;
//         }
//     }
// };
// function<void(int, int)> dfs2 = [&](int u, int last) -> void {
//     if (maxlencnt[u]) {
//         for (int i : tree[u]) {
//             if (i != last) {
//                 if (longest[i] <= longest[u] + 1) {
//                     longest[i]   = longest[u] + 1;
//                     maxlencnt[i] = 1;
//                 }
//             }
//         }
//     } else {
//         for (int i : tree[u]) {
//             if (i == last) continue;
//             if (longest[i] + 1 == longest[u]) continue;
//             if (longest[i] <= longest[u] + 1) {
//                 longest[i]   = longest[u] + 1;
//                 maxlencnt[i] = 1;
//             }
//         }
//     }
//     for (int i : tree[u]) {
//         if (i == last) continue;
//         dfs2(i, u);
//     }
// };
// dfs(1, 1);
// dfs2(1, 1);
//
// for (int i = 1; i <= n2; i++) {
//     int  r  = D - long2[i] - 1;
//     auto it = lower_bound(long1.begin() + 1, long1.end(), r);
//     ans += long2[i] * (long1.end() - it);
// }
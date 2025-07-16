#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
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
    map<pair<int, int>, int> pair_2_idx;
    vector<pair<int, int>>   idx_2_pair(3 * n + 50);
    vector<vector<int>>      graph(3 * n + 50);
    int                      cnt = 0;
    vector<int>              first_go(n + 1);
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        vector<int> tp(d);
        for (int j = 0; j < d; j++) {
            cin >> tp[j];
        }
        first_go[i] = tp[0];
        for (int j = 0; j < d; j++) {
            pair<int, int> pair1 = {tp[j], i};
            pair<int, int> pair2 = {i, tp[(j + 1) % d]};
            if (!pair_2_idx.contains(pair1)) {
                idx_2_pair[cnt]   = pair1;
                pair_2_idx[pair1] = cnt++;
            }
            if (!pair_2_idx.contains(pair2)) {
                idx_2_pair[cnt]   = pair2;
                pair_2_idx[pair2] = cnt++;
            }
            graph[pair_2_idx[pair1]].pb(pair_2_idx[pair2]);
        }
    }
    vector<int> stak;
    vector<int> vis(cnt);
    vector<int> nums(cnt);
    auto        dfs = [&](auto&& dfs, int u) -> void {
        if (vis[u]) return;
        vis[u] = 1;
        stak.eb(u);
        for (int v : graph[u]) {
            dfs(dfs, v);
        }
    };
    for (int i = 0; i < cnt; i++) {
        if (vis[i]) continue;
        stak.clear();
        dfs(dfs, i);
        vector<pair<int, int>> corridors;
        for (int ele : stak) {
            auto [u, v] = idx_2_pair[ele];
            if (u > v) swap(u, v);
            corridors.pb({u, v});
        }
        sor(corridors);
        corridors.erase(unique(all(corridors)), corridors.end());
        for (int ele : stak) {
            nums[ele] = corridors.size();
        }
        stak.clear();
    }
    for (int i = 1; i <= n; i++) {
        int u = i, v = first_go[i];
        int idx = pair_2_idx[{u, v}];
        cout << nums[idx] << '\n';
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
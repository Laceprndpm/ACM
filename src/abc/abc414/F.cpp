#include <array>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
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

struct ArrayHash {
    inline constexpr size_t operator()(const array<int, 3>& arr) const
    {
        size_t h = 0;
        for (int x : arr) {
            h ^= hash<int>()(x) + 0x9e3779b9 + (h << 6) + (h >> 2);
        }
        return h;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        graph[u].eb(v, i);
        graph[v].eb(u, i + n - 1);
    }
    vector<int> dis(n, -1);
    deque<int>  dq;
    dq.pb(0);
    vector<int>            buffer;
    vector<array<int, 20>> memory(2 * n);
    auto                   dfs = [&](auto&& dfs, int u, int fa, int cur_dist) -> void {
        if (cur_dist != k) {
            for (auto [v, idx] : graph[u]) {
                if (v == fa) continue;
                if (memory[idx][cur_dist]) continue;
                memory[idx][cur_dist] = 1;
                dfs(dfs, v, u, cur_dist + 1);
            }
        } else {
            if (dis[u] != -1) return;
            buffer.pb(u);
        }
    };
    dis[0] = 0;
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        dfs(dfs, u, u, 0);
        for (int i : buffer) {
            dq.pb(i);
            dis[i] = dis[u] + 1;
        }
        buffer.clear();
    }
    for (int i = 1; i < n; i++) {
        cout << dis[i] << ' ';
    }
    cout << '\n';
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
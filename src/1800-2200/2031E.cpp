#include <functional>
#include <iostream>
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
    vector<int>         par(n);
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 1; i < n; i++) {
        cin >> par[i];
        par[i]--;
        graph[par[i]].push_back(i);
        graph[i].push_back(par[i]);
    }

    auto dfs = [&](this auto&& dfs, int u, int fa, int depth) -> int {
        priority_queue<int, vector<int>, greater<>> sonsDepth;
        for (int v : graph[u]) {
            if (v == fa) continue;
            int res = dfs(v, u, depth + 1);
            sonsDepth.push(res);
        }
        while (sonsDepth.size() > 2) {
            int a = sonsDepth.top();
            sonsDepth.pop();
            int b = sonsDepth.top();
            sonsDepth.pop();
            int c = max(a, b) + 1;
            sonsDepth.push(c);
        }
        int ret = 1;
        if (sonsDepth.size() == 2) {
            int a = sonsDepth.top();
            sonsDepth.pop();
            int b = sonsDepth.top();
            sonsDepth.pop();
            ret = max(a, b) + 1;
        } else if (sonsDepth.size() == 1) {
            ret = sonsDepth.top() + 1;
        }
        return ret;
    };
    int res = dfs(0, 0, 0);
    cout << res - 1 << '\n';
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
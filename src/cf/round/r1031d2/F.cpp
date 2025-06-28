#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
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

// vector<int> build_eulerian(int n, vector<unordered_set<int>> graph, vector<int> deg)
{
    int s = -1, t = -1, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 1) {
            cnt++;
            if (s == -1) {
                s = i;
            } else if (t == -1) {
                t = i;
            }
        }
    }
    assert(cnt == 2 || cnt == 0);
    if (s == -1) {
        s = 1;
    }
    auto dfs = [&](auto self, int u) -> void {
        while (graph[u].size()) {
            int v = *graph[u].begin();
            graph[u].erase(graph[u].find(v));
            graph[v].erase(graph[v].find(u));
            self(self, v);
        }
        ans.push_back(u);
    };
    dfs(dfs, s);
    reverse(ans.begin(), ans.end());
    return ans;
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
    int n;
    cin >> n;
    vector<int> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    vector<set<int>> graph(2 * n + 1);
    for (int i = 0; i < n; i++) {
        int u = arr[i], v = brr[i];
        graph[u].insert(v);
        graph[v].insert(u);
    }
    auto dfs = [&](auto self, int u) -> void {
        while (graph[u].size()) {
            int v = *graph[u].begin();
            graph[u].erase(graph[u].find(v));
            graph[v].erase(graph[v].find(u));
            self(self, v);
        }
        vector<int> ans;
        ans.push_back(u);
    };
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
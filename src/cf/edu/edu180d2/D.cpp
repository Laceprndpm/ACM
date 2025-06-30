#include <cassert>
#include <cstdio>
#include <iostream>
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
    vector<vector<int>> graph(n);
    vector<int>         deg(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    auto dfs = [&](auto&& self, int s, int fa, int stat) -> void {
        for (int v : graph[s]) {
            if (v == fa) continue;
            if (stat == 0)
                printf("%d %d\n", s + 1, v + 1);
            else
                printf("%d %d\n", v + 1, s + 1);
            self(self, v, s, !stat);
        }
    };
    auto bootLoader = [&](int s) {
        printf("Yes\n");
        assert(graph[s].size() == 2);
        auto [u, v] = pair<int, int>{graph[s][0], graph[s][1]};
        printf("%d %d\n", v + 1, s + 1);
        dfs(dfs, u, s, 1);
        printf("%d %d\n", s + 1, u + 1);
        dfs(dfs, v, s, 0);
    };
    for (int i = 0; i < n; i++) {
        if (deg[i] == 2) {
            bootLoader(i);
            return;
        }
    }
    cout << "No\n";
}

signed main(signed argc, char** argv)
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    // 显然，默认有n-1对了
    // 如何找到额外的那对？明显长度最长为2
    // 我要找到树上的一段
    // a<-b<-c...
    //    |
    //    V
    //    d...
    //
    //      ...A<-B<-C...
    // 选择b为中间节点，任选cd作为源
    // 不可能，b必有一个入度和一个出度，所以度数只能为2
    // 和叶节点无关，只要度数为2即可
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
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 * @brief 并查集
 * 0-index
 */
struct DSU {
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) : component(n)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }

    std::vector<std::vector<int>> getGroups(void)
    {
        std::vector<std::vector<int>>   res;
        std::map<int, std::vector<int>> mp;
        for (int i = 0; i < f.size(); i++) {
            mp[find(i)].emplace_back(i);
        }
        res.reserve(mp.size());
        for (auto& [_, group] : mp) {
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

vector<int> build_eulerian(int n, vector<unordered_set<int>> graph, vector<int> deg)
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
    vector<int> ans;
    auto        dfs = [&](auto self, int u) -> void {
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

void solve()
{

    int n;
    cin >> n;
    vector<pair<i64, i64>>   graph(n);
    map<pair<i64, i64>, i64> or2eg;
    vector<i64>              raw2th;
    for (int i = 0; i < n; i++) {
        cin >> graph[i].first >> graph[i].second;
        graph[i].second += 1e9;
        or2eg[graph[i]]                          = i + 1;
        or2eg[{graph[i].second, graph[i].first}] = i + 1;
        raw2th.push_back(graph[i].first);
        raw2th.push_back(graph[i].second);
    }
    sort(raw2th.begin(), raw2th.end());
    raw2th.erase(unique(raw2th.begin(), raw2th.end()), raw2th.end());
    map<i64, i64> th2raw;
    int           sz = raw2th.size();
    for (int i = 0; i < sz; i++) {
        th2raw[raw2th[i]] = i;
    }
    // 是不是一个二分图匹配？
    // 或者让我们直接把它转换成一个普通图，然后求欧拉路径
    vector<int>                deg(sz);
    vector<unordered_set<int>> g(sz);
    DSU                        dsu(sz);
    for (int i = 0; i < n; i++) {
        int u = th2raw[graph[i].first], v = th2raw[graph[i].second];
        deg[u]++;
        deg[v]++;
        g[u].insert(v);
        g[v].insert(u);
        dsu.merge(u, v);
    }
    int cnt_odd = 0;
    for (int i = 0; i < sz; i++) {
        if (deg[i] % 2 == 1) {
            cnt_odd++;
        }
    }
    if (((cnt_odd != 2) && (cnt_odd != 0)) || dsu.component != 1) {
        cout << "NO\n";
        return;
    }
    function<int(int, int)> trans = [&](int u, int v) {
        u = raw2th[u], v = raw2th[v];
        return or2eg[{u, v}];
    };
    auto        res = build_eulerian(sz, std::move(g), std::move(deg));
    vector<int> ans;
    for (int i = 0; i < (int)res.size() - 1; i++) {
        ans.push_back(trans(res[i], res[i + 1]));
    }
    cout << "Yes\n";
    for (int i : ans) {
        cout << i << ' ';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
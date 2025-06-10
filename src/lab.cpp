/**
 * @brief 并查集
 * 0-index
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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

vector<int> Eulerian(int n, vector<unordered_set<int>> graph, vector<int> deg)
{
    int s = -1, t = -1, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2 == 0) {
            cnt++;
        } else if (s == -1) {
            s = i;
        } else if (t == -1) {
            t = i;
        }
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

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    return 0;
}
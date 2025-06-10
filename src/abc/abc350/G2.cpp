#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

constexpr int MOD = 998244353;

struct DSU {
private:
    std::vector<int> f, siz;

public:
    DSU() {}

    DSU(int n)
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

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<int>                          father(n + 1);
    DSU                                  dsu(n + 1);
    function<void(const int, const int)> reb = [&](const int root, const int last) {
        if (father[root] != 0) reb(father[root], root);
        father[root] = last;
    };
    i64 xl = 0;
    while (q--) {
        i64 u, v, c;
        cin >> c >> u >> v;
        c = 1 + ((c * (1 + xl)) % MOD) % 2;
        u = 1 + ((u * (1 + xl)) % MOD) % n;
        v = 1 + ((v * (1 + xl)) % MOD) % n;
        if (c == 1) {
            if (dsu.size(u) > dsu.size(v)) {
                swap(u, v);
            }
            reb(u, v);
            dsu.merge(u, v);
        } else {
            if (father[u] == father[v] && father[u] != 0) {
                xl = father[u];
            } else if (father[father[u]] == v) {
                xl = father[u];
            } else if (father[father[v]] == u) {
                xl = father[v];
            } else {
                xl = 0;
            }
            cout << xl << '\n';
        }
    }
    return 0;
}
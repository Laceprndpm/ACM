/**
 * @brief 并查集
 * 0-index
 */
struct DSU {
    int              component;
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) : component(n) { init(n); }

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

    bool same(int x, int y) { return find(x) == find(y); }

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

    int size(int x) { return siz[find(x)]; }

    std::vector<std::vector<int>> getGroups(void)
    {
        std::vector<std::vector<int>> res;
        std::vector<std::vector<int>> groups(f.size());
        for (int i = 0; i < f.size(); i++) {
            groups[find(i)].emplace_back(i);
        }
        for (int i = 0; i < f.size(); i++) {
            if (groups[i].empty()) continue;
            res.emplace_back(std::move(group));
        }
        return res;
    }
};
#include <bits/stdc++.h>

#include <map>
#include <vector>

struct DSU {
    std::vector<int> f, siz;

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
        for (auto &[_, group] : mp) {
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

using namespace std;

const int C = 26;

int main()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    if (s == t) {
        cout << 0 << endl;
        return 0;
    }
    vector<int> to(C, -1);
    for (int i = 0; i < n; i++) {
        int sc = s[i] - 'a';
        int tc = t[i] - 'a';
        if (to[sc] != -1 and to[sc] != tc) {
            cout << -1 << endl;
            return 0;
        }
        to[sc] = tc;
    }
    bool        is_perm = true;
    vector<int> tmp     = to;
    sort(tmp.begin(), tmp.end());
    for (int i = 0; i < C; i++) {
        is_perm &= (tmp[i] == i);
    }
    if (is_perm) {
        cout << -1 << '\n';
        return 0;
    }
    int         ans = 0;
    vector<int> in_deg(C);
    DSU         uf(C);
    for (int i = 0; i < C; i++) {
        if (to[i] != -1) {
            if (to[i] != i) {
                ans++;
            }
            in_deg[to[i]]++;
            uf.merge(i, to[i]);
        }
    }
    vector<vector<int>> groups{uf.getGroups()};
    for (const vector<int> &g : groups) {
        bool is_cycle = true;
        for (int i : g) {
            is_cycle &= (in_deg[i] == 1);
        }
        if (is_cycle and g.size() > 1) {
            ans++;
        }
    }
    cout << ans << endl;
}

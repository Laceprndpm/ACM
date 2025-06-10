#include <ios>
#include <iostream>
#include <map>
#include <numeric>
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
private:
    std::vector<int> f, siz;
    vector<int>      color;
    vector<int>      left, right;
    vector<int>      colornum;

public:
    DSU() {}

    DSU(int n) : color(n), left(n), right(n), colornum(n, 1)
    {
        init(n);
    }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        std::iota(color.begin(), color.end(), 0);
        iota(left.begin(), left.end(), -1);
        iota(right.begin(), right.end(), 1);
        left[0]      = 0;
        right[n - 1] = n - 1;
        siz.assign(n, 1);
    }

    int find(int x) noexcept
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

    bool merge(int x, int y) noexcept
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

    void change(int x, int c)
    {
        int hd = find(x);
        colornum[color[hd]] -= size(hd);
        color[hd] = c;
        colornum[c] += size(hd);
        int lefthd = find(left[hd]);
        if (color[lefthd] == c) {
            left[hd] = left[lefthd];
            merge(hd, lefthd);
        }
        int righthd = find(right[hd]);
        if (color[righthd] == c) {
            right[hd] = right[righthd];
            merge(hd, righthd);
        }
    }

    int getColorNum(int x)
    {
        return colornum[x];
    }

    std::vector<std::vector<int>> getGroups(void) noexcept
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
    DSU dsu(n);
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int x, c;
            cin >> x >> c;
            x--, c--;
            dsu.change(x, c);
        } else {
            int c;
            cin >> c;
            c--;
            cout << dsu.getColorNum(c) << '\n';
        }
    }
    return 0;
}

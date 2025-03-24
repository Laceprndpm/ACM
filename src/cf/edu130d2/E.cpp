#include <functional>
#include <numeric>
#include <set>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct DSU {
    std::vector<int> f, siz;
    int              num;

    DSU() {}

    DSU(int n) : num(n)
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
        num--;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }

    int size(int x)
    {
        return siz[find(x)];
    }
};

struct point {
    int x, y;
};

struct edge {
    int u, v;
    int dist;

    bool operator<(edge& t)
    {
        return dist < t.dist;
    }
};

int dF(point& x, point& y)
{
    return abs(x.x - y.x) + abs(x.y - y.y);
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
    // 3 x 2 x 1 = 6
    // 假设颜色开始相同，那么必然从最近的点对开始相同，这两个点必须与所有的其他点的距离，除了彼此都相同
    int n;
    cin >> n;
    DSU                 dsu(n);
    vector<point>       points(n + 1);
    vector<vector<int>> distM(n + 1, vector<int>(n + 1));
    set<int>            edgeLen;
    function<bool(int, int)> cmp = [&](int x, int y) {
        for (int i = 1; i <= n; i++) {
            if ()
        }
    };
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = {x, y};
        for (int j = 1; j < i; j++) {
            edgeLen.insert(dF(points[j], points[i]));
        }
    }

    for (int d : edgeLen) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (distM[i][j] <= d) {
                }
            }
        }
    }
    return 0;
}
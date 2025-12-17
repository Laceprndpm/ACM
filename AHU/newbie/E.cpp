#include <functional>
#include <iostream>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
using ll  = long long;
using i64 = long long;

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
#define mt      make_tuple
#define fi      first
#define se      second

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
};

void solve()
{
    int n, m;
    cin >> n >> m;
    DSU    dsu(n);
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < n; i++) {
        if (t[i] == '1') {
            s[i] = !(s[i] - '0') + '0';
        }
        if (s[i] == '1')
            dsu.siz[i] = 1;
        else
            dsu.siz[i] = 0;
    }
    for (int i = 0, x, y; i < m; i++) {
        cin >> x >> y;
        dsu.merge(--x, --y);
    }
    bool ok = 1;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) {
            if (dsu.size(i) % 2 != 0) {
                ok = 0;
            }
        }
    }
    cout << (ok ? "Yes\n" : "No\n");
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}

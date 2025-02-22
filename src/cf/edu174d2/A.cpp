#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

struct DSU {
    std::vector<int> f, siz;

    DSU()
    {
    }

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
};

void solve()
{
    int n;
    cin >> n;
    DSU         uf(n + 1);
    vector<int> brr(n);
    for (int i = 2; i <= n - 1; i++) {
        cin >> brr[i];
    }
    for (int i = 2; i <= n - 1; i++) {
        if (brr[i]) {
            uf.merge(i - 1, i);
            uf.merge(i, i + 1);
        }
    }
    for (int i = 2; i <= n - 1; i++) {
        if (!brr[i]) {
            if (uf.same(i - 1, i) && uf.same(i, i + 1)) {
                cout << "NO" << '\n';
                return;
            }
        }
    }
    cout << "Yes" << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
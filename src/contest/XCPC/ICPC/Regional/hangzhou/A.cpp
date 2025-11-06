#include <numeric>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct DSU {
    std::vector<int> f, siz;

    DSU() {}

    DSU(int n) { init(n); }

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
        return true;
    }

    int size(int x) { return siz[find(x)]; }
};

void solve()
{
    DSU    dsu(26);
    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    i64 slen = s1.length();
    if (slen != s2.length()) {
        cout << "NO\n";
        return;
    }
    if (slen != s3.length()) {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < slen; i++) {
        dsu.merge(s1[i] - 'a', s2[i] - 'a');
    }
    for (int i = 0; i < slen; i++) {
        if (!dsu.same(s1[i] - 'a', s3[i] - 'a')) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
    return;
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
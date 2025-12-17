#include <deque>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
    int                 component;
    std::vector<int>    f, siz;
    vector<vector<int>> pos;

    DSU() {}

    DSU(int n) : component(n) { init(n); }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        pos.assign(n, {});
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
        if (siz[x] < siz[y]) {
            swap(pos[x], pos[y]);
        }
        pos[x].ins(pos[x].end(), all(pos[y]));
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    int size(int x) { return siz[find(x)]; }
};

void solve()
{
    int q;
    cin >> q;
    vector<vector<int>> pos(5e5 + 5);
    int                 ptr   = 0;
    auto                merge = [&](int x, int y) {
        if (pos[x].size() < pos[y].size()) {
            swap(pos[x], pos[y]);
        }
        pos[x].ins(pos[x].end(), all(pos[y]));
        pos[y].clear();
    };
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        int x, y;
        if (cmd == 1) {
            cin >> x;
            pos[x].pb(ptr++);
        } else {
            cin >> x >> y;
            if (x == y) continue;
            merge(y, x);
        }
    }
    vector<int> ans(ptr);
    for (int i = 0; i <= 5e5; i++) {
        for (int p : pos[i]) {
            ans[p] = i;
        }
    }
    for (int i : ans) {
        cout << i << ' ';
    }
    cout << '\n';
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
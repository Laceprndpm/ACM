#include <unistd.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <numeric>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF = 1e9;

/**
 * @brief 并查集
 * 0-index
 */
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
        for (auto &[_, group] : mp) {
            res.emplace_back(std::move(group));
        }
        return res;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &i : arr) {
        cin >> i;
    }
    DSU         dsu(n);
    vector<int> idx(n);
    iota(all(idx), 0);
    stable_sort(all(idx), [&](int a, int b) {
        return arr[a] > arr[b];
    });
    int mx = arr[idx[0]];
    // if (idx[0] - 1 >= 0) {
    //     idx.erase(find(all(idx), idx[0] - 1));
    // }
    // if (idx[0] + 1 < n) {
    //     idx.erase(find(all(idx), idx[0] + 1));
    // }
    int                   ok  = 0;
    int                   num = 0;
    int                   ans = -INF;
    vector<array<int, 2>> big(n);
    vector<int>           enable(n);
    for (int i = 0; i < idx.size(); i++) {
        int curI = idx[i];
        int mn   = arr[curI];
        if (mn == mx) {
            big[curI][curI % 2] = 1;
        }
        if (curI + 1 < n) {
            int s2Idx = curI + 1;
            if (enable[s2Idx]) {
                num -= (dsu.size(s2Idx) + 1) / 2;
                if (big[s2Idx][s2Idx % 2] || dsu.size(s2Idx) % 2 == 0 && (big[s2Idx][0] || big[s2Idx][1])) {
                    ok--;
                }
                dsu.merge(curI, s2Idx);
                big[curI][0] |= big[s2Idx][0];
                big[curI][1] |= big[s2Idx][1];
            }
        }
        if (curI - 1 >= 0) {
            int s1Idx = dsu.find(curI - 1);
            if (enable[s1Idx]) {
                num -= (dsu.size(s1Idx) + 1) / 2;
                if (big[s1Idx][s1Idx % 2] || (dsu.size(s1Idx) % 2 == 0 && (big[s1Idx][0] || big[s1Idx][1]))) {
                    ok--;
                }
                dsu.merge(s1Idx, curI);
                big[s1Idx][0] |= big[curI][0];
                big[s1Idx][1] |= big[curI][1];
            }
        }
        curI         = dsu.find(curI);
        enable[curI] = 1;
        num += (dsu.size(curI) + 1) / 2;
        if (big[curI][curI % 2] || dsu.size(curI) % 2 == 0 && (big[curI][0] || big[curI][1])) {
            ok++;
        }
        ans = max(ans, mx + mn + num - (ok ? 0 : 1));
    }
    cout << ans << '\n';
}

signed main(signed argc, char **argv)
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
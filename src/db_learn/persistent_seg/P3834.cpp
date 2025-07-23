#include <bits/stdc++.h>
#include <sched.h>

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

// #pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
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
#define len(x)  (int)(x.size())
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

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF  = 1e9;
constexpr int MAXN = 5e5;

struct presistent {
    int tot;
    int rt[MAXN + 10];
    int ls[(MAXN << 5) + 10], rs[(MAXN << 5) + 10];

    int info[(MAXN << 5) + 10];

    int length;

    int clone(int p)
    {
        info[++tot] = info[p];
        ls[tot]     = ls[p];
        rs[tot]     = rs[p];
        return tot;
    };

    int update(int p, int l, int r, int k, int x)
    {  // 插入操作
        int dir = clone(p);
        if (r - l == 1) {
            info[dir] += x;
            return dir;
        }
        int mid = (l + r) >> 1;
        if (k < mid)
            ls[dir] = update(ls[dir], l, mid, k, x);
        else
            rs[dir] = update(rs[dir], mid, r, k, x);
        info[dir] = info[ls[dir]] + info[rs[dir]];
        return dir;
    }

    int update(int root, int k, int x = 1)
    {
        return update(root, 0, length, k, x);
    }

    int query(int u, int v, int l, int r, int k)
    {
        int mid = (l + r) >> 1;
        if (r - l == 1) return l;
        int left_val = info[ls[v]] - info[ls[u]];
        if (k <= left_val) {
            return query(ls[u], ls[v], l, mid, k);
        } else {
            return query(rs[u], rs[v], mid, r, k - left_val);
        }
    }

    int query(int u, int v, int k)
    {
        return query(u, v, 0, length, k);
    }

    void init(int length_)
    {
        tot = 0;

        function<int(int, int)> build = [&](int l, int r) -> int {
            int p = ++tot;
            if (r - l == 1) {
                return p;
            }
            int m   = (l + r) / 2;
            ls[p]   = build(l, m);
            rs[p]   = build(m, r);
            info[p] = info[ls[p]] + info[rs[p]];
            return p;
        };
        rt[0]  = build(0, length_);
        length = length_;
    }
} tree;

signed main(signed argc, char** argv)

{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    vector<int> idx_val = arr;
    sort(all(idx_val));
    idx_val.erase(unique(all(idx_val)), idx_val.end());
    for (int i = 0; i < n; i++) {
        arr[i] = lower_bound(all(idx_val), arr[i]) - bg(idx_val);
    }
    tree.init(n);
    for (int i = 0; i < n; i++) {
        tree.rt[i + 1] = tree.update(tree.rt[i], arr[i]);
    }
    for (int i = 0; i < m; i++) {
        int u, v, k;
        cin >> u >> v >> k;
        u--;
        int idx = tree.query(tree.rt[u], tree.rt[v], k);
        cout << idx_val[idx] << '\n';
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
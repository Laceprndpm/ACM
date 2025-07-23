#include <bits/stdc++.h>

// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx2,popcnt")
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
#define len(x)  int(x.size())
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

constexpr int INF = 1e9;

constexpr int MAXN = 1e6 + 50;  // 数据范围

struct presistent {
    int tot, n, m;
    int val[(MAXN << 5) + 10];
    int root[MAXN + 10];
    int ls[(MAXN << 5) + 10], rs[(MAXN << 5) + 10];
    int a[MAXN + 10], ind[MAXN + 10], length;

    int update(int k, int x, int l, int r, int root)
    {  // 插入操作
        int dir = ++tot;
        ls[dir] = ls[root], rs[dir] = rs[root];
        if (r - l == 1) {
            val[dir] = x;
            return dir;
        }
        int mid = (l + r) >> 1;
        if (k < mid)
            ls[dir] = update(k, x, l, mid, ls[dir]);
        else
            rs[dir] = update(k, x, mid, r, rs[dir]);
        return dir;
    }

    int query(int p, int l, int r, int k)
    {  // 查询操作
        int mid = (l + r) >> 1;
        if (r - l == 1) return val[p];
        if (k < mid)  // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
            return query(ls[p], l, mid, k);
        else  // 否则说明在右儿子中
            return query(rs[p], mid, r, k);
    }

    void init(const vector<int>& arr)
    {
        tot = 0;

        function<int(int, int)> build = [&](int l, int r) -> int {
            int root = ++tot;
            if (r - l == 1) {
                val[root] = arr[l];
                return root;
            }
            int m    = (l + r) / 2;
            ls[root] = build(l, m);
            rs[root] = build(m, r);
            return root;
        };
        length  = arr.size();
        root[0] = build(0, length);
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
    tree.init(arr);
    for (int i = 1; i <= m; i++) {
        int v, cmd, p;
        cin >> v >> cmd >> p;
        p--;
        if (cmd == 1) {
            int c;
            cin >> c;
            tree.root[i] = tree.update(p, c, 0, tree.length, tree.root[v]);
        } else {
            cout << tree.query(tree.root[v], 0, tree.length, p) << '\n';
            tree.root[i] = tree.root[v];
        }
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
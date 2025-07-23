#include <bits/stdc++.h>

#include <functional>
#include <iostream>
#include <vector>
#pragma GCC optimize("Ofast,unroll-loops")
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

int ceil_log2(u64 x)
{
    if (x == 0) return 0;
    return (64 - __builtin_clzll(x - 1ull));
}

struct presistent {
    int         n;
    int         tot;
    vector<int> rt;
    vector<int> ls, rs;

    struct Info {
        int a      = 0;
        int b      = 0;
        i64 contri = 0;
        i64 remain = 0;
        i64 need   = 0;

        friend Info operator+(const Info& a, const Info& b)
        {
            Info c;
            c.contri = a.contri + b.contri + min(b.need, a.remain);
            c.need   = a.need + b.need - min(b.need, a.remain);
            c.remain = a.remain + b.remain - min(b.need, a.remain);
            return c;
        }
    };

    vector<Info> info;

    int clone(int p)
    {
        info[++tot] = info[p];
        ls[tot]     = ls[p];
        rs[tot]     = rs[p];
        return tot;
    };

    int update_a(int last_p, int l, int r, int k, int x)
    {
        int dir = clone(last_p);
        if (r - l == 1) {
            info[dir].a = x;
            i64 contri  = min(info[dir].a, info[dir].b);
            i64 remain  = info[dir].a - contri;
            i64 need    = info[dir].b - contri;
            info[dir]   = Info{info[dir].a, info[dir].b, contri, remain, need};
            return dir;
        }
        int mid = (l + r) >> 1;
        if (k < mid)
            ls[dir] = update_a(ls[dir], l, mid, k, x);
        else
            rs[dir] = update_a(rs[dir], mid, r, k, x);
        info[dir] = info[ls[dir]] + info[rs[dir]];
        return dir;
    }

    int update_a(int last_p, int k, int x)
    {
        return update_a(last_p, 0, n, k, x);
    }

    int update_b(int last_p, int l, int r, int k, int x)
    {
        int dir = clone(last_p);
        if (r - l == 1) {
            info[dir].b = x;
            i64 contri  = min(info[dir].a, info[dir].b);
            i64 remain  = info[dir].a - contri;
            i64 need    = info[dir].b - contri;
            info[dir]   = Info{info[dir].a, info[dir].b, contri, remain, need};
            return dir;
        }
        int mid = (l + r) >> 1;
        if (k < mid)
            ls[dir] = update_b(ls[dir], l, mid, k, x);
        else
            rs[dir] = update_b(rs[dir], mid, r, k, x);
        info[dir] = info[ls[dir]] + info[rs[dir]];
        return dir;
    }

    int update_b(int last_p, int k, int x)
    {
        return update_b(last_p, 0, n, k, x);
    }

    Info query(int p, int l, int r, int pl, int pr)
    {
        if (pr <= l || pl >= r) {
            return Info{};
        }
        if (l >= pl && pr >= r) {
            return info[p];
        }
        if (r - l == 1) {
            return info[p];
        }
        int mid = (l + r) >> 1;
        return query(ls[p], l, mid, pl, pr) + query(rs[p], mid, r, pl, pr);
    }

    Info query(int p, int pl, int pr)
    {
        return query(p, 0, n, pl, pr);
    }

    int query_a(int p, int l, int r, int k)
    {
        if (r - l == 1) return info[p].a;
        int mid = (l + r) >> 1;
        if (k < mid) {
            return query_a(ls[p], l, mid, k);
        } else {
            return query_a(rs[p], mid, r, k);
        }
    }

    int query_a(int p, int k)
    {
        return query_a(p, 0, n, k);
    }

    void init(int n_, int m_, const vector<int>& arr, const vector<int>& brr)
    {
        tot     = 0;
        int mem = (4 << __lg(n_)) + (m_)*ceil_log2(n_);
        rt.resize(n_ + m_);
        ls.resize(mem);
        rs.resize(mem);
        info.resize(mem);
        function<int(int, int)> build = [&](int l, int r) -> int {
            int p = ++tot;
            if (r - l == 1) {
                i64 contri = min(arr[l], brr[l]);
                i64 remain = arr[l] - contri;
                i64 need   = brr[l] - contri;
                info[p]    = Info{arr[l], brr[l], contri, remain, need};
                return p;
            }
            int m   = (l + r) / 2;
            ls[p]   = build(l, m);
            rs[p]   = build(m, r);
            info[p] = info[ls[p]] + info[rs[p]];
            return p;
        };
        rt[0] = build(0, n_);
        n     = n_;
    }
} tree;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    tree.init(n, m, arr, brr);
    for (int i = 1; i <= m; i++) {
        int cmd;
        cin >> cmd;
        tree.rt[i] = tree.rt[i - 1];
        if (cmd == 1) {
            int x, y;
            cin >> x >> y;
            x--;
            tree.rt[i] = tree.update_a(tree.rt[i], x, y);
        } else if (cmd == 2) {
            int x, y;
            cin >> x >> y;
            x--;
            tree.rt[i] = tree.update_b(tree.rt[i], x, y);
        } else if (cmd == 3) {
            int x;
            cin >> x;
            tree.rt[i] = tree.rt[x];
        } else {
            int k;
            cin >> k;
            vector<int> vec;
            for (int i = 0; i < k; i++) {
                int pos;
                cin >> pos;
                pos--;
                vec.pb(pos);
            }
            vec.pb(n);
            int  lst = 0;
            auto ini = presistent::Info{};
            for (int nxt : vec) {
                ini = ini + tree.query(tree.rt[i], lst, nxt);
                if (nxt != n) {
                    ini.remain += tree.query_a(tree.rt[i], nxt);
                    ini.contri += (ini.remain + 1) / 2;
                    ini.remain -= (ini.remain + 1) / 2;
                    lst = nxt + 1;
                }
            }
            cout << ini.contri << '\n';
        }
    }
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
#include <any>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
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

template <class Info>
struct SegmentTree {
    int          n;
    vector<Info> info;

    SegmentTree() : n(0) {}

    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(vector(n_, v_));
    }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findLast(int l, int r, F &&pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }
};

template <typename T>
struct Fenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{0});
    }

    void add(int x, const T &v)
    {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l);
    }

    int select(const T &k)
    {
        int x = 0;
        T   cur{};
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

template <class T>
struct RangeFenwick {
    int        n;
    Fenwick<T> d1, d2;

    RangeFenwick(int n_) : n(n_), d1(n_), d2(n_) {}

    void add(i64 k, T v)
    {
        T v1 = k * v;
        d1.add(k, v), d2.add(k, v1);
        // 在diff的k位置+v
    }

    void add(i64 l, i64 r, T v)
    {
        add(l, v), add(r, -v);  // 将区间加差分为两个前缀加
    }

    T getsum(i64 x)
    {
        return x * d1.sum(x) - d2.sum(x);
    }

    T getsum(i64 l, i64 r)
    {
        return getsum(r) - getsum(l);
    }
};

struct Info {
    vector<vector<int>> arr{0};
    int                 len;

    // vector<vector<vector<int>>> arr;

    void init(int len)
    {
        arr = vector<vector<int>>(len, vector<int>(4));
    }

    Info(int len_)
    {
        len = len_;
        init(len_);
    };

    void modify(int p, char c)
    {
        // init();
        int v;
        if (c == 'A') {
            v = 0;
        } else if (c == 'T') {
            v = 1;
        } else if (c == 'G') {
            v = 2;
        } else {
            v = 3;
        }
        arr[p % len][v] = 1;
    }
};

Info operator+(const Info &a, const Info &b)
{
    Info c(a.len);
    for (int i = 0; i < a.len; i++) {
        for (int j = 0; j < 4; j++) {
            c.arr[i][j] += a.arr[i][j];
            c.arr[i][j] += b.arr[i][j];
        }
    }
    return c;
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
    // GAGTTGTTAA
    // AG
    // TATGGTG -> 0
    // 是不是xzz说的那个mod 5的中位数呢
    // 每次是不是查询l - r相同位置的有多少相同的ATCG?
    string s;
    cin >> s;
    int q;
    int n = sz(s);
    // vector<Fenwick<Info>> arr;
    // for (int i = 0; i < 10; i++) {
    //     arr[i] = Fenwick<Info>(5);
    // }
    vector<Info> info;
    for (int i = 0; i < n; i++) {
        info[i] = Info(i, s[i]);
    }
    cin >> q;
    SegmentTree<Info> seg(info);
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int  p;
            char c;
            cin >> p >> c;
            p--;
            seg.modify(p, Info(p, c));
            // 10 * 10 + 9 * 9 + 8 * 8...
            // 1000的常数
        } else {
            int    l, r;
            string e;
            cin >> l >> r;
            cin >> e;
            int len_e = sz(e);
            l--, r--;
            auto res = seg.rangeQuery(l, r + 1).arr;
            int  ans = 0;
            for (int i = 0; i < len_e; i++) {
                int  real = (l + i) % len_e;
                int  v;
                char c = e[i];
                if (c == 'A') {
                    v = 0;
                } else if (c == 'T') {
                    v = 1;
                } else if (c == 'G') {
                    v = 2;
                } else {
                    v = 3;
                }
                ans += res[len_e][real][v];
            }
            cout << ans << '\n';
        }
    }
    return 0;
}

// 树状数组可压缩到
// 100000 * (1 + 10) * 10 / 2 * 4 * 4 // 1024 // 1024
// 目前: 500000
// (s长度)
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
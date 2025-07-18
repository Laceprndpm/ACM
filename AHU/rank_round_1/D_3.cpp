#include <array>
#include <cassert>
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

struct IFenwick {
    virtual ~IFenwick() {}

    virtual void           add(int pos, const void *val)     = 0;
    virtual array<int, 40> rangeSum(int l, int r, void *out) = 0;
};

template <typename T>
struct Fenwick : IFenwick {
    int            n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n, T{});
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

    array<int, 40> rangeSum(int l, int r)
    {
        auto           res = sum(r) - sum(l);
        array<int, 40> tmp;
        res.fuck(tmp);
        return tmp;
    }
};

template <int I>
struct Info {
    array<int, I * 4> arr{0};

    void init() {}

    Info()
    {
        init();
    };

    Info(int p, char c)
    {
        init();
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
        arr[(p % I) * 4 + v] = 1;
    }

    void fuck(array<int, 40> &target)
    {
        for (int i = 0; i < I * 4; i++) {
            target[i] = arr[i];
        }
    }
};

template <int I>
Info<I> operator+(const Info<I> &a, const Info<I> &b)
{
    Info<I> c;
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < 4; j++) {
            c.arr[(i * 4) + j] += a.arr[(i * 4) + j];
            c.arr[(i * 4) + j] += b.arr[(i * 4) + j];
        }
    }
    return c;
}

template <int I>
Info<I> operator-(const Info<I> &a, const Info<I> &b)
{
    Info<I> c = a;
    for (int i = 0; i < I; i++) {
        for (int j = 0; j < 4; j++) {
            c.arr[(i * 4) + j] -= b.arr[(i * 4) + j];
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
    int                q;
    int                n = sz(s);
    vector<IFenwick *> mp(10);
    for (int i = 0; i < n; i++) {
        info[i] = Info(i, s[i]);
    }
    cin >> q;
    Fenwick<Info> fuck_xzz(n);
    for (int i = 0; i < n; i++) {
        fuck_xzz.add(i, info[i]);
    }
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int  p;
            char c;
            cin >> p >> c;
            p--;
            auto cur = fuck_xzz.rangeSum(p, p + 1);
            fuck_xzz.add(p, Info(p, c) - cur);

        } else {
            int    l, r;
            string e;
            cin >> l >> r;
            cin >> e;
            int len_e = sz(e);
            l--, r--;
            auto res = fuck_xzz.rangeSum(l, r + 1).arr;
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
                ans += res[(len_e - 1) * len_e * 2 + real * 4 + v];
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
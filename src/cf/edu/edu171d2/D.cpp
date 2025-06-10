#include <cstdlib>
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

i64 n;

Fenwick<i64> arr_p, arr_pp, arr_ppp;

i64 get_exactly(i64 seg_bg, i64 num)
{
    i64 ans = 0;
    ans -= arr_pp.sum(seg_bg);
    ans += arr_pp.sum(seg_bg + num);
    ans -= arr_p.sum(seg_bg) * num;
    return ans;
}

i64 sum(i64 x)
{
    i64  l = 0, r = n;
    auto c = [&](i64 x) -> i64 {
        return x * (n + (n - x + 1)) / 2;
    };
    i64 res;
    while (l <= r) {
        i64 md = (r + l) / 2;
        if (c(md) <= x) {
            res = md;
            l   = md + 1;
        } else {
            r = md - 1;
        }
    }
    i64 ans = 0;
    ans += arr_ppp.sum(res + 1);
    i64 remain = x - c(res);
    ans += get_exactly(res + 1, remain);
    return ans;
}

void solve()
{
    cin >> n;
    arr_p   = Fenwick<i64>(n + 1);
    arr_pp  = Fenwick<i64>(n + 1);
    arr_ppp = Fenwick<i64>(n + 1);
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        i64 a = arr[i];
        arr_p.add(i, a);
    }
    for (int i = 1; i <= n; i++) {
        arr_pp.add(i, arr_p.sum(i + 1));
    }
    i64 su = arr_pp.sum(n + 1);
    for (int i = 1; i <= n; i++) {
        arr_ppp.add(i, su);
        su -= (n - i + 1ll) * arr[i];
    }
    int q;
    cin >> q;
    while (q--) {
        i64 l, r;
        cin >> l >> r;
        l--;
        cout << sum(r) - sum(l) << '\n';
    }
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
    int t = 1;
    // cin >> t;
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
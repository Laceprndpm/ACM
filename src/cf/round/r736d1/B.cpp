#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

i64 my_gcd(i64 a, i64 b)  // 找到a*x + b*y = r
{

    return gcd(a, b);
}

template <class Info>
struct LazySegmentTree {
    int               n;
    std::vector<Info> info;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    LazySegmentTree(std::vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(std::vector(n_, v_));
    }

    template <class T>
    void init(std::vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
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

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F pred)
    {
        if (l >= y || r <= x || !pred(info[p])) {
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
    int findFirst(int l, int r, F pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F& pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y) {
            if (!pred.check(info[p])) {
                pred.update(info[p].x);
                return -1;
            }
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
    int findLast(int l, int r, F& pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    i64 x = 0;
};

Info operator+(Info a, Info b)
{
    return {my_gcd(a.x, b.x)};
}

struct judge {
    i64 x;

    bool check(Info info)
    {
        return my_gcd(info.x, x) == 1;
    }

    void update(i64 val)
    {
        x = my_gcd(val, x);
    }
};

void solve()
{
    i64 n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    vector<Info> diff(n - 1);
    for (int i = 0; i < n - 1; i++) {
        diff[i].x = abs(arr[i + 1] - arr[i]);
    }
    LazySegmentTree<Info> lzt(diff);
    int                   ans = 0;
    for (int i = 0; i < n - 1; i++) {
        i64  x = diff[i].x;
        auto f = judge{x};
        int  l = lzt.findLast(0, i + 1, f);
        ans    = max(ans, i - l);
    }
    cout << ans + 1 << '\n';
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
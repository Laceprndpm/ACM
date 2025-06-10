#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <class Info, class Tag>
struct LazySegmentTree {
    const int         n;
    std::vector<Info> info;
    std::vector<Tag>  tag;

    LazySegmentTree(int n) : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}

    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size())
    {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
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

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 0, n, l, r, v);
    }

    void half(int p, int l, int r)
    {
        if (info[p].act == 0) {
            return;
        }
        if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2) {
            apply(p, {-(info[p].min + 1) / 2});
            return;
        }
        int m = (l + r) / 2;
        half(2 * p, l, m);
        half(2 * p + 1, m, r);
        pull(p);
    }

    void half()
    {
        half(1, 0, n);
    }
};

constexpr i64 inf = 1E18;

struct Tag {
    i64 change = 0;
};

struct Info {
    i64 min = inf;
    i64 max = -inf;
    i64 ans = 0;
};

Info operator+(Info a, Info b)
{
    Info c;
    c.ans = max({b.max - a.min, a.ans, b.ans});
    c.min = std::min(a.min, b.min);
    c.max = std::max(a.max, b.max);
    // c.sum = a.sum + b.sum;
    // c.act = a.act + b.act;
    return c;
}

// 可以考虑更新后，答案会如何变化
// 如果更新后答案变化，那么这个点一定作为最低点或者最高点被记为答案
// 不对，也许原先的次优解会抢占
//
//
// 假如这个点变小了，那么不一定是作为最小值，可能是原先作为最大值产生贡献
// 假如这个点是作为最大点的
// 如果这个点是左端点，考虑哪个作为右端点
// 假如a[r] < a[r + k]，毫无疑问
// a[r] > a[r + k]，如果a[r] > a[r + k] + k，那么可以选择[r + k]
// 即a[i] + i > a[j] + j
// 如果这个点是右端点，考虑左端点
// a[l] > a[l - k] + k， 选择a[l - k]
// a[l] - l > a[l - k] - (l - k)
//
//
// (a[l] + l) - (a[r] + r)
// 如果al大，ar小
//
// (a[r] - r) - (a[l] - l)
// 如果al小，ar大
//
void solve()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    vector<int> brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        brr[n - 1 - i] = arr[i];
    }

    vector<Info> temp1(n), temp2(n);
    for (int i = 0; i < n; i++) {
        temp1[i].max = temp1[i].min = arr[i] - i;
        temp2[i].max = temp2[i].min = brr[i] - i;
        // temp2[i].max = temp2[i].min = arr[i] + i;
    }
    LazySegmentTree<Info, Tag> lzt_l(temp1), lzt_r(temp2);
    cout << max(lzt_l.rangeQuery(0, n).ans, lzt_r.rangeQuery(0, n).ans) << '\n';
    for (int i = 0; i < q; i++) {
        int u, x;
        cin >> u >> x;
        u--;
        lzt_l.modify(u, {x - u, x - u, 0});
        lzt_r.modify(n - 1 - u, {x - (n - 1 - u), x - (n - 1 - u), 0});
        cout << max(lzt_l.rangeQuery(0, n).ans, lzt_r.rangeQuery(0, n).ans) << '\n';
    }
}

signed main(int argc, char **argv)
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
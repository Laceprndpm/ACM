#include <tuple>
#pragma GCC optimize("O2,unroll-loops")
#pragma GCC optimize("no-stack-protector,fast-math")
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct Tag {
    i64 x{INT64_MIN};

    void apply(const Tag &t) &
    {
        x = max(x, t.x);
    }
};

struct Info {
    i64 range_max{INT64_MIN};
    i64 range_min{INT64_MAX};
    i64 range_sum{0};

    void apply(const Tag &t, i64 c) &
    {
        // range_max = range_max & t.x;
        if (t.x <= range_min) {
            return;
        }
        range_max = t.x;
        range_min = t.x;
        range_sum = t.x * c;
    }
};

Info operator+(const Info &a, const Info &b)
{
    return {max(a.range_max, b.range_max), min(a.range_min, b.range_min), a.range_sum + b.range_sum};
}

struct LazySegmentTree {
    i64          n;
    vector<Info> info;
    vector<Tag>  tag;
    vector<i64>  leftB;
    vector<i64>  rightB;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int _n, Info _v = Info())
    {
        init(_n, _v);
    }

    template <class T>
    LazySegmentTree(vector<T> &_init)
    {
        init(_init);
    }

    void init(int _n, Info _v = Info())
    {
        init(vector(_n, _v));
    }

    template <class T>
    void init(const vector<T> &_init)
    {
        n = _init.size() - 1;
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        leftB.resize(4 << __lg(n));
        rightB.resize(4 << __lg(n));
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            leftB[p]  = l;
            rightB[p] = r;
            if (r == l) {
                info[p] = _init[l];
                return;
            }
            int m = (r - l) / 2 + l;
            build(p << 1, l, m);
            build(p << 1 | 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p)
    {
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v, rightB[p] - leftB[p] + 1);
        tag[p].apply(v);
    }

    void push(int p)
    {
        apply(p << 1, tag[p]);
        apply(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }

    i64 rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return info[p].range_sum;
        }
        if (l > y || r < x) {
            return Info().range_sum;
        }
        int m = (r - l) / 2 + l;
        push(p);
        return rangeQuery(p << 1, l, m, x, y) + rangeQuery(p << 1 | 1, m + 1, r, x, y);
    }

    i64 rangeQuery(int l, int r)
    {
        if (l > r) {
            return Info().range_sum;
        }
        return rangeQuery(1, 1, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l > y || r < x) {
            return;
        }
        if (info[p].range_min >= v.x) {
            return;
        }
        if (l >= x && r <= y && info[p].range_max <= v.x) {
            apply(p, v);
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        rangeApply(p << 1, l, m, x, y, v);
        rangeApply(p << 1 | 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 1, n, l, r, v);
    }

    tuple<int, i64> lower_bound_single_idx(int p, int l, int r, i64 k, int start)  // 找到第一个小于等于k的元素的索引
    {
        if (r < start) {
            return {-1, info[p].range_sum};
        }
        if (info[p].range_min > k) {
            return {-1, info[p].range_sum};
        }
        if (l == r) {
            return {l, 0};
        }
        int m = (l + r) / 2;
        push(p);
        auto &&[res, sum] = lower_bound_single_idx(p << 1, l, m, k, start);
        i64 sum2          = 0;
        if (res == -1 || res < start) {
            tie(res, sum2) = lower_bound_single_idx(p << 1 | 1, m + 1, r, k, start);
        }
        return {res, sum + sum2};
    }

    tuple<int, i64> lower_bound_single_idx(i64 k, int start = -1)  // 最高log(n)
                                                                   // 找到第一个小于等于k的元素的索引
    {
        if (info[1].range_min > k) return {-1, -1};
        return lower_bound_single_idx(1, 1, n, k, start);
    }

    tuple<int, i64> lower_bound_len_idx(int p, int l, int r, i64 k)  // 找到下一个节点的尾
    {
        if (info[p].range_sum <= k) {
            return {r, info[p].range_sum};
        }
        if (l == r) {
            if (info[p].range_sum <= k)
                return {l, info[p].range_sum};
            else
                return {l - 1, 0};
        }
        i64 m = (l + r) / 2;
        push(p);
        auto &&[res, sumR] = lower_bound_len_idx(p << 1, l, m, k);
        if (res < m) {
            return {res, sumR};
        }
        auto &&[res2, sumL] = lower_bound_len_idx(p << 1 | 1, m + 1, r, k - info[p << 1].range_sum);
        return {res2, sumL + sumR};
    }

    tuple<int, i64> lower_bound_len_idx(i64 k)
    {
        if (info[1].range_sum <= k) {
            return {n, info[1].range_sum};
        }
        return lower_bound_len_idx(1, 1, n, k);
    }
};

// Removed operator= function as it should be a member function

signed main(signed argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<Info> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        i64 val;
        cin >> val;
        arr[i].range_sum = arr[i].range_max = arr[i].range_min = val;
    }
    LazySegmentTree lzt(arr);
    while (q--) {
        int op;
        cin >> op;
        switch (op) {
            case 1: {
                i64 x, y;
                cin >> x >> y;
                auto &&[start, _] = lzt.lower_bound_single_idx(y);
                if (start != -1 && start <= x) {
                    lzt.rangeApply(start, x, {y});
                }
                break;
            }
            case 2: {
                i64 x, y;
                cin >> x >> y;
                i64 ans   = 0;
                i64 start = x;
                while (true) {
                    auto &&[nstart, sumY] = lzt.lower_bound_single_idx(y, start);  // 获取start, log(n)
                    if (nstart == -1) {
                        break;
                    }
                    start = nstart;
                    y += sumY;                                      // log(n)
                    auto [end, sumR] = lzt.lower_bound_len_idx(y);  // log(n)
                    ans += end - start + 1;
                    start = end + 1;
                    if (start == n + 1) {
                        break;
                    }
                    y -= sumR;  // log(n)
                }
                cout << ans << '\n';
            }
        }
    }
    return 0;
}
#include <cstdint>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = unsigned long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int _n, Info _v = Info())
    {
        init(_n, _v);
    }

    template <class T>
    LazySegmentTree(const vector<T> &_init)
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
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r == l) {
                info[p] = _init[l];
                return;
            }
            int m = (r - l) / 2 + l;
            build((p << 1), l, m);
            build((p << 1) + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p)
    {
        info[p] = info[p << 1] + info[(p << 1) + 1];
    }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p)
    {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r == l) {
            info[p] = v;
            return;
        }
        int m = ((r - l) >> 1) + l;
        push(p);
        if (x <= m) {
            modify(p << 1, l, m, x, v);
        } else {
            modify((p << 1) + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 1, n, p, v);
    }

    Info rangeQuery(int l, int r)
    {
        if (l > r) {
            return Info();
        }
        return rangeQuery(1, 1, n, l, r);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return info[p];
        }
        if (l > y || r < x) {
            return Info();
        }
        int m = ((r - l) >> 1) + l;
        push(p);
        return rangeQuery(p << 1, l, m, x, y) + rangeQuery((p << 1) + 1, m + 1, r, x, y);
    }

    int rangeQuery2(int p, int l, int r, int x, int y, int k)
    {
        if (l > y || r < x) {
            return -1;
        }
        if (l >= x && r <= y && (info[p].x >> k & 1)) {
            return -1;
        }
        if (r == l) {
            if (info[p].x >> k & 1) {
                return -1;
            } else {
                return l;
            }
        }
        int m = (l + r) / 2;
        push(p);
        int res = rangeQuery2(2 * p, l, m, x, y, k);
        if (res == -1) {
            res = rangeQuery2(2 * p + 1, m + 1, r, x, y, k);
        }
        return res;
    }

    int rangeQuery2(int l, int r, int k)  // 最高log(n)
    {
        return rangeQuery2(1, 1, n, l, r, k);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l > y || r < x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (r - l) / 2 + l;
        push(p);
        rangeApply(p << 1, l, m, x, y, v);
        rangeApply((p << 1) + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 1, n, l, r, v);
    }
};

struct Tag {
    i64 x{INT64_MAX};

    void apply(const Tag &t) &
    {
        x = x & t.x;
    }
};

struct Info {
    int lenInfo{0};
    i64 range_max{INT64_MAX};
    i64 y{0};

    void apply(const Tag &t) &
    {
        range_max = range_max & t.x;
        if (lenInfo == 1) {
            y = range_max ^ INT64_MAX;
        } else {
            y &= t.x;
        }
    }
};

Info operator+(const Info &a, const Info &b)
{
    Info res;
    res.lenInfo   = a.lenInfo + b.lenInfo;
    res.range_max = a.range_max & b.range_max;
    res.y         = (a.y ^ b.y) & (a.range_max | b.range_max);
    return res;
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
    i64 n, q;
    cin >> n >> q;
    vector<Info> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].range_max;
        arr[i].y       = arr[i].range_max ^ INT64_MAX;
        arr[i].lenInfo = 1;
    }
    LazySegmentTree<Info, Tag> lzt(arr);
    while (q--) {
        i64 op;
        i64 l, r, x, p;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            lzt.rangeApply(l, r, {x});
        } else if (op == 2) {
            cin >> p >> x;
            lzt.modify(p, Info{1, x, x ^ INT64_MAX});
        } else if (op == 3) {
            cin >> l >> r;
            auto val = lzt.rangeQuery(l, r);  // log(n)
            if (val.y != 0) {                 // O(1)
                int i;
                for (int j = 62; j >= 0; j--) {
                    if ((val.y >> j & 1) == 1) {
                        i = j;
                        break;
                    }
                }
                int place = lzt.rangeQuery2(l, r, i);                                                     // log(n)
                cout << (lzt.rangeQuery(l, place - 1) + lzt.rangeQuery(place + 1, r)).range_max << '\n';  // 2*log(n)
            } else
                cout << val.range_max << '\n';
        }
    }

    return 0;
}
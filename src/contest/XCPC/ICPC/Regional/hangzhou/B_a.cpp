#include <cstdint>
#include <functional>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
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
    LazySegmentTree(vector<T> _init)
    {
        init(_init);
    }

    void init(int _n, Info _v = Info())
    {
        init(vector(_n, _v));
    }

    template <class T>
    void init(vector<T> _init)
    {
        n = _init.size();
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
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v, rightB[p] - leftB[p] + 1);
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
        int m = (r - l) / 2 + l;
        push(p);
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 1, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= x && r <= y) {
            return info[p];
        }
        if (l > y || r < x) {
            return Info();
        }
        int m = (r - l) / 2 + l;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        if (l > r) {
            return Info();
        }
        return rangeQuery(1, 1, n, l, r);
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
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 1, n, l, r, v);
    }

    int rangeQuery2(int l, int r, int x)
    {
        if (l == r) {
            return l;
        }
        int  mid   = (r - l) / 2 + l;
        bool lzero = ((rangeQuery(l, mid).x >> x & 1) == 0);
        bool rzero = (rangeQuery(mid + 1, r).x >> x & 1) == 0;
        if (lzero && rzero) {
            return -1;
        }
        if (lzero) {
            return rangeQuery2(l, mid, x);
        }
        if (rzero) {
            return rangeQuery2(mid + 1, r, x);
        }
        return -1;
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
    i64 x{INT64_MAX};

    void apply(const Tag &t, i64 c) &
    {
        x = x & t.x;
    }
};

// Removed operator= function as it should be a member function

Info operator+(const Info &a, const Info &b)
{
    return {a.x & b.x};
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
    i64 n, q;
    cin >> n >> q;
    vector<Info> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i].x;
    }
    LazySegmentTree<Info, Tag> lzt(arr);
    while (q--) {
        i64 op;
        cin >> op;
        if (op == 1) {
            i64 l, r, x;
            cin >> l >> r >> x;
            lzt.rangeApply(l, r, {x});
        } else if (op == 2) {
            i64 p, x;
            cin >> p >> x;
            lzt.modify(p, {x});
        } else if (op == 3) {
            i64 l, r;
            cin >> l >> r;
            i64 m    = (r - l) / 2 + l;
            int flag = true;
            i64 val  = lzt.rangeQuery(l, m).x;
            i64 var  = lzt.rangeQuery(m + 1, r).x;
            for (int i = 62; i >= 0; i--) {
                if (((val >> i & 1) ^ (var >> i & 1)) == 1) {
                    i64 p = lzt.rangeQuery2(l, r, i);
                    if (p != -1) {
                        cout << (lzt.rangeQuery(l, p - 1) + lzt.rangeQuery(p + 1, r)).x << '\n';
                        flag = false;
                        break;
                    }
                }
            }
            if (flag) cout << (val & var) << '\n';
        }
    }
    return 0;
}
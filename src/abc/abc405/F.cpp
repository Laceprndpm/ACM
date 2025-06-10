#include <chrono>
#include <functional>
#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 *@brief 懒加载线段树
 */
struct Tag {
    i64 x;

    void apply(const Tag &t) &
    {
        x = x & t.x;
    }
};

struct Info {
    set<int> x;

    void apply(const Tag &t, i64 c) &
    {
        x.insert(t.x);
    }
};

// Removed operator= function as it should be a member function

Info operator+(const Info &a, const Info &b)
{
    set<int> x;
    if (a.x.size() < b.x.size()) {
        for (auto i : a.x) {
            if (b.x.count(i) == 0) {
                
            }
        }
    }
    return ;
}

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
};

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    LazySegmentTree return 0;
}
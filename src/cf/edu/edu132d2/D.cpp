#include <functional>
#include <utility>
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
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
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
        int m = (r - l) / 2 + l;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
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
        return rangeQuery(1, 0, n, l, r);
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
        return rangeApply(1, 0, n, l, r, v);
    }
};

struct Tag {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        x = x + t.x;
    }
};

struct Info {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        x = max(x, t.x);
    }
};

// Removed operator= function as it should be a member function

Info operator+(const Info &a, const Info &b)
{
    return {max(a.x, b.x)};
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
    int n, m;
    cin >> n >> m;
    vector<Info> ai(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> ai[i].x;
    }
    LazySegmentTree<Info, Tag> lzt(ai);
    int                        q;
    cin >> q;
    while (q--) {
        int xs, ys, xf, yf, k;
        cin >> xs >> ys >> xf >> yf >> k;
        if (abs(xf - xs) % k != 0 || abs(yf - ys) % k != 0) {
            cout << "No\n";
            continue;
        }
        int xk   = (n - xs) / k;
        int maxY = xk * k + xs;
        if (ys > yf) {
            swap(ys, yf);
        }
        if (maxY > lzt.rangeQuery(ys, yf).x) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
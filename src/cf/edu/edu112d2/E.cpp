#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct seg {
    int l, r, w;
};

/**
 *@brief 懒加载线段树
 */
struct Tag {
    i64 x;

    void apply(const Tag &t) &
    {
        x = x + t.x;
    }
};

struct Info {
    i64 x;

    void apply(const Tag &t) &
    {
        x += t.x;
    }
};

// Removed operator= function as it should be a member function

Info operator+(const Info &a, const Info &b)
{
    return {min(a.x, b.x)};
}

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
        function<void(int, int, int)> build = [&](int p, int l, int r) {
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
    int n, m;
    cin >> n >> m;
    vector<seg> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].l >> arr[i].r >> arr[i].w;
    }
    vector<Info>    vec(m, Info{0});
    LazySegmentTree lzt(vec);
    int             l = 0, r = 1e6;
    sort(arr.begin(), arr.end(), [&](seg &a, seg &b) {
        return a.w < b.w;
    });
    function<bool(int)> check = [&](int x) -> bool {
        int  lp = 0, rp = 0;
        bool ok = false;
        for (; rp < n && !ok; rp++) {
            lzt.rangeApply(arr[rp].l, arr[rp].r - 1, {1});
            while (arr[lp].w + x < arr[rp].w) {
                lzt.rangeApply(arr[lp].l, arr[lp].r - 1, {-1});
                lp++;
            }
            if (lzt.rangeQuery(1, m - 1).x > 0) {
                ok = true;
            }
        }
        while (lp < rp) {
            lzt.rangeApply(arr[lp].l, arr[lp].r - 1, {-1});
            lp++;
        }
        return ok;
    };
    int ans;
    while (l <= r) {
        int mid = (r + l) / 2;
        if (check(mid)) {
            r   = mid - 1;
            ans = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << '\n';
    // 如何做到O(n)的检查？做一个LzTree，则每次更新是Log(m),总时间复杂度为O(nlog(m)log(w)) 400 * 3 * 1e5 = 1e8

    return 0;
}
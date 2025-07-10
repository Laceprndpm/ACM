#include <algorithm>
#include <array>
#include <functional>
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

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    LazySegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(vector(n_, v_));
    }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
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
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
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
        push(p);
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
        push(p);
        half(2 * p, l, m);
        half(2 * p + 1, m, r);
        pull(p);
    }

    void half()
    {
        half(1, 0, n);
    }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findLast(int l, int r, F &&pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }

    void maintainL(int p, int l, int r, int pre)
    {
        if (info[p].difl > 0 && info[p].maxlowl < pre) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainL(2 * p, l, m, pre);
        pre = max(pre, info[2 * p].max);
        maintainL(2 * p + 1, m, r, pre);
        pull(p);
    }

    void maintainL()
    {
        maintainL(1, 0, n, -1);
    }

    void maintainR(int p, int l, int r, int suf)
    {
        if (info[p].difr > 0 && info[p].maxlowr < suf) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainR(2 * p + 1, m, r, suf);
        suf = max(suf, info[2 * p + 1].max);
        maintainR(2 * p, l, m, suf);
        pull(p);
    }

    void maintainR()
    {
        maintainR(1, 0, n, -1);
    }
};

struct Tag {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        x = (x + t.x);
    }
};

struct Info {
    i64 x = 0;

    void apply(const Tag &t) &
    {
        x = x + t.x;
    }
};

Info operator+(const Info &a, const Info &b)
{
    return {max(a.x, b.x)};
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
    int n, m;
    cin >> n >> m;
    vector<array<i64, 3>> command(m);
    for (int i = 0; i < m; i++) {
        cin >> command[i][0] >> command[i][1] >> command[i][2];
    }
    sort(all(command), [&](const auto &a, const auto &b) {
        return a[1] < b[1];
    });

    LazySegmentTree<Info, Tag> segment_tree(n + 1);
    for (int i = 1, j = 0; i <= n; i++) {
        segment_tree.modify(i, segment_tree.rangeQuery(0, i));
        while (j < m && command[j][1] == i) {
            segment_tree.rangeApply(command[j][0], command[j][1] + 1, {command[j][2]});
            j++;
        }
    }
    cout << segment_tree.rangeQuery(0, n + 1).x;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
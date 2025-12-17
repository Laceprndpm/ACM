

template <class Info, class Tag>
struct LazySegmentTree {
    int                   n;
    int                   len;
    vector<Info>          info;
    vector<Tag>           tag;
    vector<array<int, 2>> sons;
    int                   tot;

    LazySegmentTree(int n_, int len_ = 2) : n(n_), len(len_) { init(); }

    int newnode(int p)  // 预留备用
    {
        info.pb(Info());
        tag.pb(Tag());
        sons.pb({0, 0});
        return ++tot;
    }

    void init()
    {
        info.reserve(len);
        tag.reserve(len);
        sons.reserve(len);
        info.resize(2), tag.resize(2), sons.resize(2, {0, 0});
        tot = 1;
    }

    void pull(int p) { info[p] = info[sons[p][0]] + info[sons[p][1]]; }

    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p)
    {
        if (sons[p][0] == 0) sons[p][0] = newnode(p);
        if (sons[p][1] == 0) sons[p][1] = newnode(p);
        apply(sons[p][0], tag[p]);
        apply(sons[p][1], tag[p]);
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
            modify(sons[p][0], l, m, x, v);
        } else {
            modify(sons[p][1], m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }

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
        return rangeQuery(sons[p][0], l, m, x, y) + rangeQuery(sons[p][1], m, r, x, y);
    }

    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }

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
        rangeApply(sons[p][0], l, m, x, y, v);
        rangeApply(sons[p][1], m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v) { return rangeApply(1, 0, n, l, r, v); }

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
        half(sons[p][0], l, m);
        half(sons[p][1], m, r);
        pull(p);
    }

    void half() { half(1, 0, n); }

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
        int res = findFirst(sons[p][0], l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(sons[p][1], m, r, x, y, pred);
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
        int res = findLast(sons[p][1], m, r, x, y, pred);
        if (res == -1) {
            res = findLast(sons[p][0], m, x, y, pred);
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
        maintainL(sons[p][0], l, m, pre);
        pre = max(pre, info[2 * p].max);
        maintainL(sons[p][1], m, r, pre);
        pull(p);
    }

    void maintainL() { maintainL(1, 0, n, -1); }

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
        maintainR(sons[p][1], m, r, suf);
        suf = max(suf, info[2 * p + 1].max);
        maintainR(sons[p][0], l, m, suf);
        pull(p);
    }

    void maintainR() { maintainR(1, 0, n, -1); }
};

struct Tag {
    int x = 0;

    void apply(const Tag &t) & { x = max(x, t.x); }
};

struct Info {
    int x = 0;

    void apply(const Tag &t) & { x = max(x, t.x); }
};

Info operator+(const Info &a, const Info &b) { return {max(a.x, b.x)}; }

void solve() { LazySegmentTree<Info, Tag> lzt(2); }

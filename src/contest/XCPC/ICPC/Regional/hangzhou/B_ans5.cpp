#include <bits/stdc++.h>
#define ll long long

using namespace std;

// 懒标记线段树 by jiangly
template <class Info, class Tag>
struct LazySegmentTree {
    int          n;     // 原序列长度
    vector<Info> info;  // 结点信息
    vector<Tag>  tag;   // 结点懒标记信息

    // 三种构造函数，按照需求选择即可
    // 也可以选择第一种，然后调用n次modify
    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }  // 初始为同一种结点

    template <class T>
    LazySegmentTree(vector<T> init_)
    {
        init(init_);
    }  // 针对序列初始化

    void init(int n_, Info v_ = Info()) { init(vector(n_, v_)); }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        // 结点信息为左闭右开
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m), build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }  // 向上合并结点

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
    }  // 懒标记下传

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

    void modify(int p, const Info &v) { modify(1, 0, n, p, v); }  // 懒人专属

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
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v) { return rangeApply(1, 0, n, l, r, v); }  // 懒人专属

    int find(int p, int l, int r, int x, int y, int k)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && (info[p].x >> k & 1)) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = find(2 * p, l, m, x, y, k);
        if (res == -1) {
            res = find(2 * p + 1, m, r, x, y, k);
        }
        return res;
    }

    int find(int l, int r, int k) { return find(1, 0, n, l, r, k); }
};

// 根据具体情况修改

constexpr ll ALL = LLONG_MAX;

struct Tag {
    ll x = ALL;

    void apply(const Tag &t) & { x &= t.x; }
};

struct Info {
    int len = 0;
    ll  x = ALL, y = 0;

    void apply(const Tag &t) &
    {
        x &= t.x;
        if (len == 1)
            y = x ^ ALL;
        else
            y &= t.x;
    }
};

Info operator+(const Info &a, const Info &b)
{
    Info res;
    res.len = a.len + b.len;
    res.x   = a.x & b.x;
    res.y   = (a.y ^ b.y) & (a.x | b.x);
    return res;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<ll>                 a(n);
    LazySegmentTree<Info, Tag> tr(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tr.modify(i, {1, a[i], a[i] ^ ALL});
    }

    while (q--) {
        int op, l, r, s;
        cin >> op;
        ll x;
        if (op == 1) {
            cin >> l >> r >> x;
            l--;
            tr.rangeApply(l, r, {x});
        } else if (op == 2) {
            cin >> s >> x;
            s--;
            tr.modify(s, {1, x, x ^ ALL});
        } else {
            cin >> l >> r;
            l--;
            auto res = tr.rangeQuery(l, r);
            ll   x = res.x, y = res.y;
            if (y) {
                int k;
                for (int j = 62; j >= 0; j--) {
                    if (y >> j & 1) {
                        k = j;
                        break;
                    }
                }
                int j = tr.find(l, r, k);
                x     = tr.rangeQuery(l, j).x & tr.rangeQuery(j + 1, r).x;
            }
            cout << x << '\n';
        }
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}
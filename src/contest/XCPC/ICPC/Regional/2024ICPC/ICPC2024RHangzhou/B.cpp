#include <bits/stdc++.h>

#include <cassert>
#include <vector>
using namespace std;
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
#define mt      make_tuple
#define fi      first
#define se      second
using i64 = long long;
using u64 = unsigned long long;
u64 ans   = 0;

template <class Info, class Tag>
struct LazySegmentTree {
    int               n;
    std::vector<Info> info;
    std::vector<Tag>  tag;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }

    template <class T>
    LazySegmentTree(std::vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }

    template <class T>
    void init(std::vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
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

    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }

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

    void rangeApply(int l, int r, const Tag &v) { return rangeApply(1, 0, n, l, r, v); }

    template <class F>
    int myFind(int p, int l, int r, int x, int y, F pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (x <= l && r <= y && !pred(info[p])) {
            ans &= info[p].x;
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = myFind(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = myFind(2 * p + 1, m, r, x, y, pred);
        } else {
            ans &= rangeQuery(2 * p + 1, m, r, x, y).x;
        }
        return res;
    }

    template <class F>
    int myFind(int l, int r, F pred)
    {
        return myFind(1, 0, n, l, r, pred);
    }
};

constexpr u64 B = (1ull << 63) - 1;

struct Tag {
    u64 x = B;

    void apply(Tag t) { x &= t.x; }
};

struct Info {
    u64 x    = B;
    u64 loss = 0;

    // a & b = 0
    // a | b = 1
    // a ^ b = 1
    void apply(Tag t)
    {
        x &= t.x;
        if (!(loss >> 63 & 1))
            loss &= t.x;
        else
            loss = x ^ B | 1ull << 63;
    }
};

Info operator+(Info a, Info b)
{
    Info c;
    c.x    = a.x & b.x;
    c.loss = (a.loss & b.x) | (b.loss & a.x);
    return c;
}

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<Info> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i].x;
        arr[i].loss = (arr[i].x ^ B) | (1ull << 63);
    }
    LazySegmentTree<Info, Tag> lzt(std::move(arr));
    u64                        found = 0;

    auto pred = [&found](const Info &x) -> bool { return x.loss & found; };
    while (q--) {
        int op;
        cin >> op;
        switch (op) {
            case 1: {
                int l, r;
                cin >> l >> r;
                l--;
                u64 x;
                cin >> x;
                lzt.rangeApply(l, r, {x});
                break;
            }
            case 2: {
                int s;
                cin >> s;
                u64 x;
                cin >> x;
                lzt.modify(s - 1, {x, (x ^ B) | 1ull << 63});
                break;
            }
            case 3: {
                int l, r;
                cin >> l >> r;
                l--;
                auto res    = lzt.rangeQuery(l, r);
                u64  target = res.loss;
                for (int i = 63; i >= 0; i--) {
                    if (target >> i & 1ull) {
                        found = 1ull << i;
                        break;
                    }
                }
                if (found) {
                    ans     = B;
                    int mid = lzt.myFind(l, r, pred);
                    cout << ans << '\n';
                } else {
                    cout << res.x << '\n';
                }
                found = 0;
            }
        }
    }
    cout << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) {
        solve();
    }
}

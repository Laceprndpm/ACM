#include <bits/stdc++.h>

using u32  = unsigned int;
using i64  = long long;
using u64  = unsigned long long;
using f64  = long double;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

template <class T>
constexpr bool chmax(T& x, T y)
{
    if (y > x) {
        x = y;
        return true;
    }
    return false;
}

template <class T>
constexpr bool chmin(T& x, T y)
{
    if (y < x) {
        x = y;
        return true;
    }
    return false;
}

template <class Info, class Tag>
    requires requires(Info info, Tag tag) {
        info.apply(tag);
        tag.apply(tag);
    }
struct LazySegmentTree {
    int               n;
    std::vector<Info> info;
    std::vector<Tag>  tag;

    LazySegmentTree() {}

    LazySegmentTree(const int& n)
    {
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
    }

    LazySegmentTree(const std::vector<Info>& a)
    {
        int n   = a.size() - 1;
        this->n = n;
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        auto work = [&](auto&& self, int p, int l, int r) {
            if (l == r) {
                info[p] = Info(a[l]);
                return;
            }
            int mid = (l + r) >> 1;
            self(self, p << 1, l, mid), self(self, p << 1 | 1, mid + 1, r);
            info[p] = info[p << 1] + info[p << 1 | 1];
        };
        work(work, 1, 1, n);
    }

    void apply(int p, const Tag& v)
    {
        info[p].apply(v), tag[p].apply(v);
    }

    void pull(int p)
    {
        apply(p << 1, tag[p]), apply(p << 1 | 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int L, int R, const Info& v)
    {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            info[p] = v;
            return;
        }
        pull(p);
        int mid = (l + r) >> 1;
        modify(p << 1, l, mid, L, R, v), modify(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void modify(int p, const Info& v)
    {
        modify(1, 1, n, p, p, v);
    }

    Info rangeQuery(int p, int l, int r, int L, int R)
    {
        if (l > R or r < L) {
            return Info();
        }
        if (L <= l and r <= R) {
            return info[p];
        }
        pull(p);
        int mid = (l + r) >> 1;
        return rangeQuery(p << 1, l, mid, L, R) + rangeQuery(p << 1 | 1, mid + 1, r, L, R);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 1, n, l, r);
    }

    void rangeApply(int p, int l, int r, int L, int R, const Tag& v)
    {
        if (l > R or r < L) {
            return;
        }
        if (L <= l and r <= R) {
            apply(p, v);
            return;
        }
        pull(p);
        int mid = (l + r) >> 1;
        rangeApply(p << 1, l, mid, L, R, v), rangeApply(p << 1 | 1, mid + 1, r, L, R, v);
        info[p] = info[p << 1] + info[p << 1 | 1];
    }

    void rangeApply(int l, int r, const Tag& v)
    {
        rangeApply(1, 1, n, l, r, v);
    }

    template <class F>
    int findFirst(int p, int l, int r, int L, int R, F pred)
    {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        pull(p);
        int mid = (l + r) >> 1;
        int res = findFirst(p << 1, l, mid, L, R, pred);
        return res == -1 ? findFirst(p << 1 | 1, mid + 1, r, L, R, pred) : res;
    }

    template <class F>
    int findFirst(int l, int r, F pred)
    {
        return findFirst(1, 1, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int L, int R, F pred)
    {
        if (l > R or r < L or not pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        pull(p);
        int mid = (l + r) >> 1;
        int res = findLast(p << 1 | 1, mid + 1, r, L, R, pred);
        return res == -1 ? findLast(p << 1, l, mid, L, R, pred) : res;
    }

    template <class F>
    int findLast(int l, int r, F pred)
    {
        return findLast(1, 1, n, l, r, pred);
    }

    template <class F>
    int findPrefixFirst(int p, int l, int r, int L, int R, const F& pred, Info& pref)
    {
        if (l > R or r < L) {
            return r + 1;
        }
        if (L <= l and r <= R) {
            if (l != r) {
                pull(p);
            }
            if (not pred(pref + info[p])) {
                pref = pref + info[p];
                return r + 1;
            }
            if (l == r) {
                return l;
            }
            int mid = (l + r) >> 1;
            int res;
            if (pred(pref + info[p << 1])) {
                res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
            } else {
                pref = pref + info[p << 1];
                res  = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
            }
            return res;
        }
        int mid = (l + r) >> 1;
        pull(p);
        int res = mid + 1;
        if (L <= mid) {
            res = findPrefixFirst(p << 1, l, mid, L, R, pred, pref);
        }
        if (res == mid + 1 and mid + 1 <= R) {
            res = findPrefixFirst(p << 1 | 1, mid + 1, r, L, R, pred, pref);
        }
        return res;
    }

    template <class F>
    int findPrefixFirst(int l, int r, const F& pred)
    {
        Info pref = Info();
        int  res  = findPrefixFirst(1, 1, n, l, r, pred, pref);
        return res == r + 1 ? -1 : res;
    }

    template <class F>
    int findSurfixLast(int p, int l, int r, int L, int R, const F& pred, Info& surf)
    {
        if (l > R or r < L) {
            return l - 1;
        }
        if (L <= l and r <= R) {
            if (l != r) {
                pull(p);
            }
            if (not pred(surf + info[p])) {
                surf = surf + info[p];
                return l - 1;
            }
            if (l == r) {
                return r;
            }
            int mid = (l + r) >> 1;
            int res;
            if (pred(surf + info[p << 1 | 1])) {
                res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
            } else {
                surf = surf + info[p << 1 | 1];
                res  = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
            }
            return res;
        }
        int mid = (l + r) >> 1;
        int res = mid;
        pull(p);
        if (mid + 1 <= R) {
            res = findSurfixLast(p << 1 | 1, mid + 1, r, L, R, pred, surf);
        }
        if (L <= mid and res == mid) {
            res = findSurfixLast(p << 1, l, mid, L, R, pred, surf);
        }
        return res;
    }

    template <class F>
    int findSurfixLast(int l, int r, const F& pred)
    {
        Info surf = Info();
        int  res  = findSurfixLast(1, 1, n, l, r, pred, surf);
        return res == l - 1 ? -1 : res;
    }
};

constexpr i64 inf = std::numeric_limits<i64>::max();

struct Tag {
    i64 x = inf;

    void apply(const Tag& t)
    {
        if (t.x != inf) {
            x &= t.x;
        }
    }
};

struct Info {
    int l = 0;
    i64 s = inf;
    i64 h = 0;

    void apply(const Tag& t)
    {
        if (t.x == inf) {
            return;
        }
        if (l == 1) {
            s &= t.x;
            h = ~s;
        } else {
            s &= t.x;
            h &= t.x;
        }
    }

    constexpr friend Info operator+(const Info& a, const Info& b)
    {
        Info c{};
        if (a.l == 0) {
            return b;
        }
        if (b.l == 0) {
            return a;
        }
        c.l = a.l + b.l;
        c.s = (a.s & b.s);
        c.h = ((a.h & b.s) | (a.s & b.h));
        return c;
    }
};

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    constexpr int    Kw = 63;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        std::cin >> a[i];
    }

    LazySegmentTree<Info, Tag> seg(n);
    for (int i = 1; i <= n; i += 1) {
        seg.modify(i, {1, a[i], ~a[i]});
    }

    for (int t = 1; t <= q; t += 1) {
        int o;
        std::cin >> o;

        if (o == 1) {
            i64 x;
            int l, r;
            std::cin >> l >> r >> x;

            seg.rangeApply(l, r, {x});
        } else if (o == 2) {
            i64 x;
            int p;
            std::cin >> p >> x;
            seg.modify(p, {1, x, ~x});
        } else if (o == 3) {
            int l, r;
            std::cin >> l >> r;

            auto v = seg.rangeQuery(l, r);
            if (v.h == 0) {
                std::cout << v.s << '\n';
            } else {
                int p = std::__lg(v.h);
                int f = seg.findFirst(l, r, [&](const auto& e) {
                    return (~e.s >> p & 1);
                });

                assert(f != -1);

                auto res = inf;

                if (f != l) {
                    res &= seg.rangeQuery(l, f - 1).s;
                }
                if (f != r) {
                    res &= seg.rangeQuery(f + 1, r).s;
                }

                std::cout << res << '\n';
            }
        } else {
            assert(false);
        }
    }
    return 0;
}
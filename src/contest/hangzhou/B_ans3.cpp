#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int split(int tl, int tr)
{
    int lg = 1 << __lg(tr - tl);
    return min(tl + lg, tr - lg / 2);
}

struct S {
    ll n, could, would;  // bits that have >= n-1, bits that have all
};

using F = ll;

S init(ll x)
{
    return S{1, (1ull << 63) - 1, x};
}

S e()
{
    return S{0, (1ull << 63) - 1, (1ull << 63) - 1};
}

F id()
{
    return (1ull << 63) - 1;
}

S mapping(F r, S l)
{
    if (l.n == 1)
        return S{l.n, l.could, l.would & r};
    else
        return S{l.n, l.could & r, l.would & r};
}

F composition(F l, F r)
{
    return l & r;
}

S op(S l, S r)
{
    if (l.n == 0) return r;
    if (r.n == 0) return l;
    return S{l.n + r.n, l.could & r.could & (l.would | r.would), l.would & r.would};
}

struct lazy_segtree {
    int            _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    lazy_segtree(int n) : _n(n), size(bit_ceil((unsigned)n)), log(__lg(size)), d(2 * size, e()), lz(size, id()) {}

    void update(int k)
    {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }

    void all_apply(int k, F f)
    {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }

    void push(int k)
    {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }

    void set(int p, S x)
    {
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p)
    {
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }

#define check(p)                                   \
    {                                              \
        if (((l >> i) << i) != l) p(l >> i);       \
        if (((r >> i) << i) != r) p((r - 1) >> i); \
    }

    S prod(int l, int r)
    {
        l += size, r += size;
        for (int i = log; i >= 1; i--)
            check(push);
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1, r >>= 1;
        }
        return op(sml, smr);
    }

    void apply(int l, int r, F f)
    {
        l += size, r += size;
        for (int i = log; i >= 1; i--)
            check(push);
        int l2 = l, r2 = r;
        while (l2 < r2) {
            if (l2 & 1) all_apply(l2++, f);
            if (r2 & 1) all_apply(--r2, f);
            l2 >>= 1, r2 >>= 1;
        }
        for (int i = 1; i <= log; i++)
            check(update);
    }

    template <class G>
    int max_right(int l, G g)
    {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--)
            push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    if (g(op(sm, d[l *= 2]))) sm = op(sm, d[l++]);
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <class G>
    int min_left(int r, G g)
    {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    lazy_segtree tree(n);
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        tree.set(i, init(x));
        // auto S = tree.range_prod(1, 0, n, i, i+1);
        // cout << i << ": " << b.could << " " << b.would << endl;
        // cout << x << " ";
    }
    while (q--) {
        int qt;
        cin >> qt;
        // cout << "HI " << qt << endl;
        if (qt == 1) {
            int l, r;
            ll  x;
            cin >> l >> r >> x;
            tree.apply(l - 1, r, x);
        } else if (qt == 2) {
            int s;
            ll  x;
            cin >> s >> x;
            tree.set(s - 1, init(x));
        } else {
            int l, r;
            cin >> l >> r;
            l--;
            auto tot = tree.prod(l, r);
            // cout << l << " " << r << ": " << tot.could << " " << tot.would << endl;
            if (tot.could == tot.would)
                cout << tot.would << "\n";
            else {
                ll  bb = bit_floor((unsigned long long)(tot.could ^ tot.would));
                int rr = tree.max_right(l, [&](S x) {
                    return (x.would & bb) != 0;
                });
                cout << (tree.prod(l, rr).would & tree.prod(rr + 1, r).would) << "\n";
            }
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);

    // int t; cin >> t; while (t--)
    solve();

    return 0;
}
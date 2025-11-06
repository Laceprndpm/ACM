#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll ALL = numeric_limits<ll>::max();

struct SegTree {
    using T               = pair<ll, ll>;
    using U               = pair<ll, ll>;
    static constexpr T E  = {ALL, ALL};
    static constexpr U UF = {ALL, -1};
    int                n;
    vector<T>          tree;
    vector<U>          lazy;
    int                h;
    vector<ll>         k;  // size of segments (optional)

    SegTree(const vector<T> &a)
        : n(ssize(a) + 1),
          tree(2 * n, E),
          // SegTree(int size, T def = E) : n(size + 1), tree(2 * n, def),
          lazy(n, UF),
          h(__lg(2 * n)),
          k(2 * n, 1)
    {
        ranges::copy(a, tree.begin() + n);
        for (int i = n - 1; i > 0; i--) {
            k[i]    = 2 * k[2 * i];
            tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
        }
    }

    T comb(T a, T b)
    {
        return {a.first & b.first, (a.first & b.second) | (a.second & b.first)};
    }

    void apply(int i, U val)
    {
        T &v = tree[i];
        if (val.second >= 0) {
            v = {val.second, ALL};
        } else {
            v.first &= val.first;
            if (i < n) v.second &= val.first;
        }
        if (i < n) {
            if (val.second >= 0)
                lazy[i] = val;
            else {
                lazy[i].first &= val.first;
                if (lazy[i].second >= 0) lazy[i].second &= val.second;
            }
        }
    }

    void push_down(int i)
    {
        if (lazy[i] != UF) {
            apply(2 * i, lazy[i]);
            apply(2 * i + 1, lazy[i]);
            lazy[i] = UF;
        }
    }

    void push(int i)
    {
        for (int s = h; s > 0; s--)
            push_down(i >> s);
    }

    void build(int i)
    {
        while (i /= 2) {
            push_down(i);
            tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void update(int l, int r, U val)
    {
        l += n, r += n;
        int l0 = l, r0 = r;
        push(l0), push(r0);
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }
        build(l0), build(r0);
    }

    ll query(int l, int r)
    {
        l += n, r += n;
        int savel = l, saver = r;
        push(l), push(r);
        T resL = E, resR = E;
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) resL = comb(resL, tree[l++]);
            if (r & 1) resR = comb(tree[--r], resR);
        }
        T res = comb(resL, resR);

        ll bit = bit_floor((unsigned long long)(res.first ^ res.second));
        if (bit == 0) return res.first;

        ll ans = ALL;
        l = savel, r = saver;
        for (; l < r; l /= 2, r /= 2) {
            if (l & 1) {
                if (tree[l].first & bit)
                    ans &= tree[l].first;
                else
                    ans &= query2(l, bit);
                l++;
            }
            if (r & 1) {
                r--;
                if (tree[r].first & bit)
                    ans &= tree[r].first;
                else
                    ans &= query2(r, bit);
            }
        }
        return ans;
    }

    ll query2(int i, ll bit)
    {
        ll res = ALL;
        while (i < n) {
            push_down(i);
            int l = 2 * i, r = 2 * i + 1;
            if (tree[l].first & bit)
                res &= tree[l].first, i = r;
            else if (tree[r].first & bit)
                res &= tree[r].first, i = l;
            else
                assert(0);
        }
        return res;
    }
};

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> arr(n);
    for (auto &[x, y] : arr)
        cin >> x, y = ALL;
    SegTree seg(arr);

    while (q--) {
        int op;
        cin >> op;
        switch (op) {
            case 1: {
                int l, r;
                ll  x;
                cin >> l >> r >> x, l--;
                seg.update(l, r, {x, -1});
                break;
            }
            case 2: {
                int s;
                ll  x;
                cin >> s >> x, s--;
                seg.update(s, s + 1, {ALL, x});
                break;
            }
            case 3: {
                int l, r;
                cin >> l >> r, l--;
                cout << seg.query(l, r) << "\n";
                break;
            }
        }
    }
}
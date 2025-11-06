#include <bits/stdc++.h>
#define int long long
using namespace std;
const int                N   = 1e6 + 10;
const int                mod = 998244353;
const unsigned long long m   = (1ULL << 63) - 1;

struct TR {
    int l, r;
    int a, b;  // b有哪些是有且只有一个0

    TR operator+(const TR &y) const
    {
        TR res;
        res.l = l, res.r = y.r;
        res.a = a & y.a;
        res.b = (b & y.a) | (y.b & a);
        return res;
    }
} tr[N << 2];

int lz[N << 2];
int a[N];
#define ls(i) ((i) << 1)
#define rs(i) ((i) << 1 | 1)

void push_up(int i)
{
    tr[i] = tr[ls(i)] + tr[rs(i)];
}

void push_down(int i)
{
    if (lz[i] != m) {
        lz[ls(i)] &= lz[i];
        lz[rs(i)] &= lz[i];
        if (tr[ls(i)].l == tr[ls(i)].r) {
            tr[ls(i)].a &= lz[i];
            tr[ls(i)].b = m ^ tr[ls(i)].a;
        } else {
            tr[ls(i)].a &= lz[i];
            tr[ls(i)].b &= lz[i];
        }
        if (tr[rs(i)].l == tr[rs(i)].r) {
            tr[rs(i)].a &= lz[i];
            tr[rs(i)].b = m ^ tr[rs(i)].a;
        } else {
            tr[rs(i)].a &= lz[i];
            tr[rs(i)].b &= lz[i];
        }
        lz[i] = m;
    }
}

void build(int i, int l, int r)
{
    tr[i].l = l, tr[i].r = r;
    lz[i] = m;
    if (l == r) {
        tr[i] = {l, r, a[l], (int)m ^ a[l]};
        return;
    }
    int mid = (l + r) >> 1;
    build(ls(i), l, mid);
    build(rs(i), mid + 1, r);
    push_up(i);
}

void upd1(int i, int l, int r, int nl, int nr, int k)
{
    if (l >= nl && r <= nr) {
        if (l == r) {
            tr[i].a &= k;
            tr[i].b = m ^ tr[i].a;
        } else {
            tr[i].a &= k;
            tr[i].b &= k;
            lz[i] &= k;
        }
        return;
    }
    int mid = (l + r) >> 1;
    push_down(i);
    if (nl <= mid) {
        upd1(ls(i), l, mid, nl, nr, k);
    }
    if (nr > mid) {
        upd1(rs(i), mid + 1, r, nl, nr, k);
    }
    push_up(i);
}

void upd2(int i, int l, int r, int x, int k)
{
    if (l == r) {
        tr[i].a = k;
        tr[i].b = m ^ k;
        return;
    }
    int mid = (l + r) >> 1;
    push_down(i);
    if (x <= mid) {
        upd2(ls(i), l, mid, x, k);
    } else {
        upd2(rs(i), mid + 1, r, x, k);
    }
    push_up(i);
}

TR query(int i, int l, int r, int ql, int qr)
{
    if (l >= ql && r <= qr) return tr[i];
    int mid = (l + r) >> 1;
    push_down(i);
    if (ql > mid) return query(rs(i), mid + 1, r, ql, qr);
    if (qr <= mid) return query(ls(i), l, mid, ql, qr);
    return query(ls(i), l, mid, ql, qr) + query(rs(i), mid + 1, r, ql, qr);
}

int query2(int i, int l, int r, int ql, int qr, int k)
{
    if (ql > r || qr < l) return -1;
    if (tr[i].a >> k & 1) {
        return -1;
    }
    if (l == r) {
        return l;
    }
    int mid = (l + r) >> 1;
    push_down(i);
    int res = query2(ls(i), l, mid, ql, qr, k);
    if (res == -1) {
        return query2(rs(i), mid + 1, r, ql, qr, k);
    }
    return res;
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build(1, 1, n);
    int op, l, r, x;
    while (q--) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;
            upd1(1, 1, n, l, r, x);
        } else if (op == 2) {
            cin >> l >> x;
            upd2(1, 1, n, l, x);
        } else {
            cin >> l >> r;
            auto res = query(1, 1, n, l, r);
            if (res.b == 0) {
                cout << res.a << '\n';
                continue;
            }
            int mx  = __lg(res.b);
            int id  = query2(1, 1, n, l, r, mx);
            int ans = m;
            if (id != l) {
                ans &= query(1, 1, n, l, id - 1).a;
            }
            if (id != r) {
                ans &= query(1, 1, n, id + 1, r).a;
            }
            cout << ans << '\n';
        }
    }
}
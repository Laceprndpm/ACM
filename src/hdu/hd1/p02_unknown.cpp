#include <bits/stdc++.h>

using ll = long long;

const int N = 2e5 + 5, V = N * 22;
const ll  inf = 1e18;

int n, q, a0[N], b0[N], yyy;

struct Matrix {
    ll a00, a01;
};

Matrix operator*(const Matrix& f, const Matrix& g)
{
    Matrix h;
    h.a00 = f.a00 + g.a00;
    h.a01 = std::max(f.a00 + g.a01, f.a01);
    return h;
}

struct SegmentTree {
    int    tot, rt[N], a[V], b[V], son[V][2];
    ll     suma[N];
    Matrix f[V];

    void reset()
    {
        rt[0]   = 0;
        suma[0] = 0;
        for (int u = tot; u >= 0; u--)
            a[u] = b[u] = son[u][0] = son[u][1] = 0;
        f[0] = (Matrix){0, -inf};
        tot  = 0;
    }

    void build(int& u, int l, int r)
    {
        u = ++tot;
        if (l + 1 >= r) {
            a[u] = a0[l];
            suma[0] += a[u];
            b[u] = b0[l];
            f[u] = (Matrix){(ll)(a[u] - b[u]), 0ll};
            return;
        }
        int mid = l + r >> 1;
        build(son[u][0], l, mid);
        build(son[u][1], mid, r);
        f[u] = f[son[u][1]] * f[son[u][0]];
    }

    void modifya(int& u, int l, int r, int p, int x)
    {
        int v     = u;
        u         = ++tot;
        a[u]      = a[v];
        b[u]      = b[v];
        son[u][0] = son[v][0];
        son[u][1] = son[v][1];
        if (l + 1 >= r) {
            yyy  = a[u];
            a[u] = x;
            f[u] = (Matrix){(ll)(a[u] - b[u]), 0ll};
            return;
        }
        int mid = l + r >> 1;
        if (p < mid)
            modifya(son[u][0], l, mid, p, x);
        else
            modifya(son[u][1], mid, r, p, x);
        f[u] = f[son[u][1]] * f[son[u][0]];
    }

    void querya(int u, int l, int r, int p, int& x)
    {
        if (l + 1 >= r) {
            x = a[u];
            return;
        }
        int mid = l + r >> 1;
        if (p < mid)
            querya(son[u][0], l, mid, p, x);
        else
            querya(son[u][1], mid, r, p, x);
    }

    void modifyb(int& u, int l, int r, int p, int x)
    {
        int v     = u;
        u         = ++tot;
        a[u]      = a[v];
        b[u]      = b[v];
        son[u][0] = son[v][0];
        son[u][1] = son[v][1];
        if (l + 1 >= r) {
            b[u] = x;
            f[u] = (Matrix){(ll)(a[u] - b[u]), 0ll};
            return;
        }
        int mid = l + r >> 1;
        if (p < mid)
            modifyb(son[u][0], l, mid, p, x);
        else
            modifyb(son[u][1], mid, r, p, x);
        f[u] = f[son[u][1]] * f[son[u][0]];
    }

    void query(int u, int l, int r, int pl, int pr, ll& x)
    {
        if (pl >= pr) return;
        if (l == pl && r == pr) {
            x = std::max(x + f[u].a00, f[u].a01);
            return;
        }
        int mid = l + r >> 1;
        if (pr <= mid)
            query(son[u][0], l, mid, pl, pr, x);
        else if (pl >= mid)
            query(son[u][1], mid, r, pl, pr, x);
        else {
            query(son[u][0], l, mid, pl, mid, x);
            query(son[u][1], mid, r, mid, pr, x);
        }
    }
} seg;

void run()
{
    std::cin >> n >> q;
    for (int i = 0; i < n; i++) {
        std::cin >> a0[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b0[i];
    }
    seg.reset();
    seg.build(seg.rt[0], 0, n);
    for (int qi = 1; qi <= q; qi++) {
        int opt;
        std::cin >> opt;
        seg.rt[qi]   = seg.rt[qi - 1];
        seg.suma[qi] = seg.suma[qi - 1];
        if (opt == 1) {
            int i, x;
            std::cin >> i >> x;
            i--;
            seg.modifya(seg.rt[qi], 0, n, i, x);
            seg.suma[qi] += x - yyy;  // yyy为修改前的金矿产值
        } else if (opt == 2) {
            int i, x;
            std::cin >> i >> x;
            i--;
            seg.modifyb(seg.rt[qi], 0, n, i, x);
        } else if (opt == 3) {
            int i;
            std::cin >> i;
            seg.rt[qi]   = seg.rt[i];
            seg.suma[qi] = seg.suma[i];
        } else {
            int k;
            std::cin >> k;
            std::vector<int> e(k);
            for (auto& x : e) {
                std::cin >> x;
                x--;
            }
            int lst = 0;
            e.push_back(n);
            ll  ans = 0;
            int a;
            for (auto i : e) {
                seg.query(seg.rt[qi], 0, n, lst, i, ans);  // 注意这里作为引用传入了
                if (i < n) {
                    seg.querya(seg.rt[qi], 0, n, i, a);
                    ans = (ans + a) / 2;
                }
                lst = i + 1;
            }
            std::cout << seg.suma[qi] - ans << "\n";
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int T;
    std::cin >> T;
    while (T--)
        run();
    return 0;
}
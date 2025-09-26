#include <bits/stdc++.h>
using namespace std;
using ll        = long long;
using i64       = long long;
using u64       = unsigned long long;
constexpr int P = 998244353;
constexpr int G = 3;

inline int addmod(int a, int b)
{
    a += b;
    if (a >= P) a -= P;
    return a;
}

inline int submod(int a, int b)
{
    a -= b;
    if (a < 0) a += P;
    return a;
}

int qpow(int x, int y)
{
    int       res = 1;
    long long a   = x;
    while (y) {
        if (y & 1) res = (int)((1LL * res * a) % P);
        a = (a * a) % P;
        y >>= 1;
    }
    return res;
}

// build bit-reversal permutation for n (n is power of two)
static void build_rev(vector<int> &rev, int n)
{
    rev.assign(n, 0);
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
}

// iterative NTT with precomputed rev
static void ntt(vector<int> &a, const vector<int> &rev, int invert)
{
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int half = len >> 1;
        int wn   = qpow(G, (P - 1) / len);
        if (invert == -1) wn = qpow(wn, P - 2);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < half; ++j) {
                int u    = a[i + j];
                int v    = (int)((1LL * a[i + j + half] * w) % P);
                a[i + j] = u + v;
                if (a[i + j] >= P) a[i + j] -= P;
                a[i + j + half] = u - v;
                if (a[i + j + half] < 0) a[i + j + half] += P;
                w = (int)((1LL * w * wn) % P);
            }
        }
    }
    if (invert == -1) {
        int inv_n = qpow(n, P - 2);
        for (int i = 0; i < n; ++i) a[i] = (int)((1LL * a[i] * inv_n) % P);
    }
}

void solve_once()
{
    int n, m, k;
    if (!(cin >> n >> m >> k)) return;
    auto   zip   = [m](int x, int y) constexpr { return y * (2 * m) + x; };  // [0, 2 * n * m - 1]
    auto   unzip = [m](i64 c) constexpr -> pair<int, int> { return pair<int, int>(c % (2 * m), c / (2 * m)); };
    int    x = 0, y = 0;
    int    mx_x = 0, mx_y = 0, mn_x = 0, mn_y = 0;
    string s;
    cin >> s;
    for (char c : s) {
        switch (c) {
            case 'U': y--; break;
            case 'D': y++; break;
            case 'L': x--; break;
            case 'R': x++; break;
        }
        mx_x = max(mx_x, x);
        mn_x = min(mn_x, x);
        mx_y = max(mx_y, y);
        mn_y = min(mn_y, y);
    }
    if (mx_x - mn_x >= m || mx_y - mn_y >= n) {
        if (k == 0) {
            cout << 1LL * n * m << '\n';
        } else {
            cout << 0 << '\n';
        }
        return;
    }
    int len     = 2 * (4 * n * m + 1) - 1;
    int reallen = 1;
    while (reallen < len) reallen <<= 1;

    vector<int> animo(reallen);
    vector<int> px(reallen);
    vector<int> rev;
    build_rev(rev, reallen);

    // fill animo
    for (int iy = -mn_y; iy < n - mx_y; ++iy) {
        int l = zip(-mn_x + m, iy + n);
        int r = zip(2 * m - mx_x, iy + n);
        if (l < 0) l = 0;
        if (r > reallen) r = reallen;
        if (l < r) fill(animo.begin() + l, animo.begin() + r, 1);
    }

    int death = (n - mx_y + mn_y) * (m - mx_x + mn_x) - k;
    x         = m;
    y         = n;
    int base  = 4 * n * m;
    int idx   = base - zip(x, y);
    if (0 <= idx && idx < reallen) px[idx] = 1;
    for (char c : s) {
        switch (c) {
            case 'U': y++; break;
            case 'D': y--; break;
            case 'L': x++; break;
            case 'R': x--; break;
        }
        idx = base - zip(x, y);
        if (0 <= idx && idx < reallen) px[idx] = 1;
    }

    ntt(px, rev, 1);
    ntt(animo, rev, 1);
    for (int i = 0; i < reallen; ++i) {
        px[i] = (int)((1LL * px[i] * animo[i]) % P);
    }
    ntt(px, rev, -1);

    int ans = 0;
    for (int c = 4 * n * m; c < 6 * n * m; ++c) {
        int  j  = c - 4 * n * m;
        auto pr = unzip(j);
        int  ax = pr.first, ay = pr.second;
        if (ax < 0 || ay < 0 || ax >= m || ay >= n) continue;
        if (px[c] != death) continue;
        ++ans;
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) solve_once();
    return 0;
}

// {1, 2x, 3x^2}
// {4, 5x, 6x^2}
// {5, 13x, 10 +12 + 6 x^2, ...}
// 
// 
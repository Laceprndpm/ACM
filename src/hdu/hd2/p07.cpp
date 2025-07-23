#include <bits/stdc++.h>

#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

// vectors
#define len(x)  int(x.size())
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

// https://trap.jp/post/1224/
#define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
#define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
#define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
#define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
#define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
#define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...)    d
#define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

constexpr int INF = 1e9;

constexpr i64 P = (1e9 + 7);

// assume -P <= x < 2P
int jianglynorm(int x)
{
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}

template <class T>
T power(T a, i64 b)
{
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

struct Z {
    int x;

    Z(int x = 0) : x(jianglynorm(x)) {}

    Z(i64 x) : x(jianglynorm(x % P)) {}

    int val() const
    {
        return x;
    }

    Z operator-() const
    {
        return Z(jianglynorm(P - x));
    }

    Z inv() const
    {
        assert(x != 0);
        return power(*this, P - 2);
    }

    Z &operator*=(const Z &rhs)
    {
        x = i64(x) * rhs.x % P;
        return *this;
    }

    Z &operator+=(const Z &rhs)
    {
        x = jianglynorm(x + rhs.x);
        return *this;
    }

    Z &operator-=(const Z &rhs)
    {
        x = jianglynorm(x - rhs.x);
        return *this;
    }

    Z &operator/=(const Z &rhs)
    {
        return *this *= rhs.inv();
    }

    friend Z operator*(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res *= rhs;
        return res;
    }

    friend Z operator+(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res += rhs;
        return res;
    }

    friend Z operator-(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res -= rhs;
        return res;
    }

    friend Z operator/(const Z &lhs, const Z &rhs)
    {
        Z res = lhs;
        res /= rhs;
        return res;
    }

    friend std::istream &operator>>(std::istream &is, Z &a)
    {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const Z &a)
    {
        return os << a.val();
    }
};

struct Comb {
    int            n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    Comb(int n) : Comb()
    {
        init(n);
    }

    void init(int m)
    {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i]        = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m)
    {
        if (m > n) init(2 * m);
        return _fac[m];
    }

    Z invfac(int m)
    {
        if (m > n) init(2 * m);
        return _invfac[m];
    }

    Z inv(int m)
    {
        if (m > n) init(2 * m);
        return _inv[m];
    }

    Z binom(int n, int m)
    {
        if (n < m || m < 0) return 0;
        if (n > 5e5) {
            Z ini(1);
            for (int i = n - m + 1; i <= n; i++) {
                ini *= i;
            }
            return ini * invfac(m);
        }
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb(4e5 + 50);

void solve()
{
    int n, R;
    cin >> n >> R;
    vector<int> ai(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    vector<pair<i64, i64>> vec;
    for (int i = n; i >= 1; i--) {
        ai[i] = max(ai[i], ai[i + 1]);
        vec.push_back({R - ai[i] + 2, i});
    }
    sort(vec.begin(), vec.end());
    vector<Z> arr(n + 1);
    vec.pb({R, n + 1});
    for (int i = 0; i < n + 1; i++) {
        arr[i] += comb.binom(vec[i].first + vec[i].second - 2, vec[i].second - 1);
        for (int j = 0; j < i; j++) {
            if (vec[j].second <= vec[i].second) {
                arr[i] -= arr[j]
                          * comb.binom(vec[i].second - vec[j].second + vec[i].first - vec[j].first,
                                       vec[i].second - vec[j].second);
            }
        }
    }
    cout << arr[n] << '\n';
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
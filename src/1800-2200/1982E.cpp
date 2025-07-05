#include <bit>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

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

constexpr int INF = 1e9;
using i64         = long long;
using u64         = unsigned long long;
using u32         = unsigned;
using u128        = unsigned __int128;

template <class T>
constexpr T power(T a, u64 b, T res = 1)
{
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P>
constexpr u32 mulMod(u32 a, u32 b)
{
    return u64(a) * b % P;
}

template <u64 P>
constexpr u64 mulMod(u64 a, u64 b)
{
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr i64 safeMod(i64 x, i64 m)
{
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr std::pair<i64, i64> invGcd(i64 a, i64 b)
{
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }

    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;

    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

template <std::unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}

    template <std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_ % mod())
    {
    }

    template <std::signed_integral T>
    constexpr ModIntBase(T x_)
    {
        using S = std::make_signed_t<U>;
        S v     = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static U mod()
    {
        return P;
    }

    constexpr U val() const
    {
        return x;
    }

    constexpr ModIntBase operator-() const
    {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const
    {
        return power(*this, mod() - 2);
    }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) &
    {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }

    constexpr ModIntBase &operator+=(const ModIntBase &rhs) &
    {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }

    constexpr ModIntBase &operator-=(const ModIntBase &rhs) &
    {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }

    constexpr ModIntBase &operator/=(const ModIntBase &rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, ModIntBase &a)
    {
        i64 i;
        is >> i;
        a = i;
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr std::strong_ordering operator<=>(const ModIntBase &lhs, const ModIntBase &rhs)
    {
        return lhs.val() <=> rhs.val();
    }

private:
    U x;
};

template <u32 P>
using ModInt = ModIntBase<u32, P>;
template <u64 P>
using ModInt64 = ModIntBase<u64, P>;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const
    {
        return m;
    }

    constexpr u32 mul(u32 a, u32 b) const
    {
        u64 z = a;
        z *= b;

        u64 x = u64((u128(z) * im) >> 64);

        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    u32 m;
    u64 im;
};

template <u32 Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}

    template <std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_ % mod())
    {
    }

    template <std::signed_integral T>
    constexpr DynModInt(T x_)
    {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(u32 m)
    {
        bt = m;
    }

    static u32 mod()
    {
        return bt.mod();
    }

    constexpr u32 val() const
    {
        return x;
    }

    constexpr DynModInt operator-() const
    {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const
    {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt &operator*=(const DynModInt &rhs) &
    {
        x = bt.mul(x, rhs.val());
        return *this;
    }

    constexpr DynModInt &operator+=(const DynModInt &rhs) &
    {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }

    constexpr DynModInt &operator-=(const DynModInt &rhs) &
    {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }

    constexpr DynModInt &operator/=(const DynModInt &rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, DynModInt &a)
    {
        i64 i;
        is >> i;
        a = i;
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const DynModInt &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr std::strong_ordering operator<=>(const DynModInt &lhs, const DynModInt &rhs)
    {
        return lhs.val() <=> rhs.val();
    }

private:
    u32            x;
    static Barrett bt;
};

template <u32 Id>
Barrett DynModInt<Id>::bt = 998244353;

using Z = ModInt<(int)(1e9 + 7)>;

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
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

struct node {
    Z   prefix, suffix, subarr;
    int vis, through;
};

void solve()
{
    i64 n, k;
    cin >> n >> k;

    vector<vector<Z>>   prefix(61, vector<Z>(61));
    vector<vector<Z>>   suffix(61, vector<Z>(61));
    vector<vector<Z>>   subarr(61, vector<Z>(61));
    vector<vector<int>> vis(61, vector<int>(61));
    vector<vector<int>> through(61, vector<int>(61));
    auto                dfs = [&](this auto &&dfs, int num1, int place) -> void {
        if (vis[num1][place]) {
            return;
        }
        if (place == 0) {
            vis[num1][place] = 1;
            if (num1 <= k) {
                subarr[num1][place] = 1;
                prefix[num1][place] = suffix[num1][place] = 1;
                through[num1][place]                      = 1;
            } else {
                subarr[num1][place] = 0;
                prefix[num1][place] = suffix[num1][place] = 0;
                through[num1][place]                      = 0;
            }
            // if (num1 < k) {
            //     subarr[num1][place]  = 3;
            //     prefix[num1][place]  = 2;
            //     suffix[num1][place]  = 2;
            //     through[num1][place] = 1;
            // } else if (num1 == k) {
            //     subarr[num1][place] = 1;
            //     prefix[num1][place] = 1;
            //     suffix[num1][place] = 0;
            // } else {
            //     subarr[num1][place] = 0;
            //     prefix[num1][place] = 0;
            //     subarr[num1][place] = 0;
            // }
            return;
        }
        dfs(num1, place - 1);
        dfs(num1 + 1, place - 1);
        subarr[num1][place] += subarr[num1][place - 1];
        subarr[num1][place] += subarr[num1 + 1][place - 1];

        if (through[num1][place - 1] && through[num1 + 1][place - 1]) {
            prefix[num1][place]  = prefix[num1][place - 1] + prefix[num1 + 1][place - 1];
            suffix[num1][place]  = suffix[num1][place - 1] + suffix[num1 + 1][place - 1];
            through[num1][place] = 1;
        } else if (through[num1][place - 1]) {
            prefix[num1][place] = prefix[num1][place - 1] + prefix[num1 + 1][place - 1];
            suffix[num1][place] = suffix[num1 + 1][place - 1];
        } else if (through[num1 + 1][place - 1]) {
            prefix[num1][place] = prefix[num1][place - 1];
            suffix[num1][place] = suffix[num1][place - 1] + suffix[num1 + 1][place - 1];
        } else {
            prefix[num1][place] = prefix[num1][place - 1];
            suffix[num1][place] = suffix[num1 + 1][place - 1];
        }

        subarr[num1][place] += suffix[num1][place - 1] * prefix[num1 + 1][place - 1];
        vis[num1][place] = 1;
    };
    int cur = 0;
    Z   ans = 0;
    for (int i = 60; i >= 0; i--) {
        if (n & 1ll << i) {
            dfs(cur, i);
            ans += subarr[cur][i];
            cur++;
        }
    }
    cout << ans << '\n';
    // 1100
    // 0111
    // 0000
    // 1011
    // 1000
    //
    // 110
    //
    // 011
    // 000
    //
    // 000
    // 001
    // 010
    // 011
    //
    // 11
    // 00
    // 01
    // 10
    //
    //
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
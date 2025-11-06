#include <bits/stdc++.h>

#include <bit>
#include <utility>
#include <vector>

using namespace std;
// vector
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
using u32 = unsigned int;

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

template <u32 P, typename... Args>
constexpr u32 mulMod(u32 a, u32 b, Args... rest)
{
    return mulMod<P>(mulMod<P>(a, b), rest...);
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

    constexpr static U mod() { return P; }

    constexpr U val() const { return x; }

    constexpr ModIntBase operator-() const
    {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const { return power(*this, mod() - 2); }

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

    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & { return *this *= rhs.inv(); }

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

    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) { return os << a.val(); }

    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) { return lhs.val() == rhs.val(); }

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
using ModInt64  = ModIntBase<u64, P>;
constexpr u32 P = 1e9 + 7;

using Z = ModInt<P>;

struct Comb {
    int            n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    Comb(int n) : Comb() { init(n); }

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
        Z res = 1;
        for (int i = 0; i < m; i++) {
            res *= (n - i);
        }
        return res * invfac(m);
        // return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

void solve()
{
    int n1, n2, m, k;
    cin >> n1 >> n2 >> m >> k;
    vector<pair<int, int>> constraints(k);
    // 对于每种蓝色的方案数，计算出红色满足他至少要多少张卡片，其他的随意即可？
    // 复杂度上界为20'9715'2000，3秒，可以勉勉强强?
    // 无法确定红色所需要的卡片种类
    // 也无法确定他必然不能缺少哪些卡牌
    //
    // ===============================
    // 可以只枚举补集的子集，作为B独享的数字，同时通过k中约束来约束出
    // 然后用sos预处理交
    //
    int maskM = 0;
    for (int i = 0; i < k; i++) {
        cin >> constraints[i].fi >> constraints[i].se;
        constraints[i].fi--;
        constraints[i].se--;

        maskM |= 1 << constraints[i].fi;
        maskM |= 1 << constraints[i].se;
    }
    const int M = __builtin_popcount(maskM);
    vector<Z> m2dp(1 << m);
    for (int m2 = 0; m2 < (1 << m); m2++) {
        bool ok = 1;
        if (m2 & (((1 << m) - 1) ^ maskM)) continue;
        for (auto [a, b] : constraints) {
            if (m2 >> a & 1 && m2 >> b & 1) {
                ok = 0;
                break;
            };
        }
        if (!ok) continue;
        m2dp[m2] = comb.binom(n1 - 1 + m - M, m - __builtin_popcount(m2) - 1);
    }
    for (int i = 0; i < m; i++)
        for (int sta = (1 << m) - 1; sta >= 0; sta--)
            if (sta & (1 << i)) m2dp[sta] += m2dp[sta ^ (1 << i)];
    Z ans = 0;
    for (int m1 = 0; m1 < (1 << m); m1++) {
        bool ok = 1;
        if (m1 & (((1 << m) - 1) ^ maskM)) continue;
        for (auto [a, b] : constraints) {
            if (m1 >> a & 1 && m1 >> b & 1) {
                ok = 0;
                break;
            };
        }
        if (!ok) continue;
        ans += comb.binom(n2 - 1 + m - M, m - __builtin_popcount(m1) - 1) * m2dp[(((1 << m) - 1) ^ m1)];
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
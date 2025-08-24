#include <algorithm>
#include <bitset>
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

namespace detail {

// 检测是否可迭代
template <class T, class = void>
struct is_iterable : std::false_type {};

template <class T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

// 递归打印
template <class T>
void smart_print(std::ostream &os, const T &val, int indent = 0)
{
    if constexpr (is_iterable<T>::value && !std::is_same_v<T, std::string>) {
        if (indent == 0) {
            os << '\n';
        }
        using element_type   = typename T::value_type;
        constexpr bool is_2d = is_iterable<element_type>::value;
        os << (is_2d ? "[\n" : "[");
        for (auto it = val.begin(); it != val.end();) {
            if constexpr (is_2d) os << std::string(indent + 2, ' ');
            smart_print(os, *it, indent + 2);
            if (++it != val.end()) os << (is_2d ? ",\n" : ", ");
        }
        os << (is_2d ? "\n" + std::string(indent, ' ') : "") << "]";
    } else {
        os << val;  // 基础类型直接输出
    }
}
}  // namespace detail

#define GREEN "\033[32m"
#define RED   "\033[31m"
#define RESET "\033[0m"

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T &val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print()
{
    dbg_wt('\n');
}

template <class Head, class... Tail>
void print(Head &&head, Tail &&...tail)
{
    dbg_wt(head);
    if (sizeof...(Tail)) dbg_wt(' ');
    print(forward<Tail>(tail)...);
}

#if defined(DEBUG)
#define dbg(...)                                    dbg_IMPL(__VA_ARGS__, dbg6, dbg5, dbg4, dbg3, dbg2, dbg1)(__VA_ARGS__)
#define dbg_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define dbg1(x)                                     print(#x, "=", (x)), flush()
#define dbg2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush()
#define dbg3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush()
#define dbg4(x, y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush()
#define dbg5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v)), flush()
#define dbg6(x, y, z, w, v, u) \
    print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
#else
#define dbg(...)
#endif
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

using Z = ModInt<998244353>;

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

namespace Poly {
constexpr int get_MAX()
{
#ifdef CLANGD_MODE
    return 1;
#else
    return 1 << 22;
#endif
}

// 缺省是因为clangd无法解析静态数组
constexpr int MAXN = get_MAX();

Z d[MAXN], b[MAXN], c[MAXN];

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change(Z y[], int len)
{
    // 一开始 i 是 0...01，而 j 是 10...0，在二进制下相反对称。
    // 之后 i 逐渐加一，而 j 依然维持着和 i 相反对称，一直到 i = 1...11。
    for (int i = 1, j = len / 2, k; i < len - 1; i++) {
        // 交换互为小标反转的元素，i < j 保证交换一次
        if (i < j) swap(y[i], y[j]);
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的。
        // 这里 k 代表了 0 出现的最高位。j 先减去高位的全为 1 的数字，直到遇到了
        // 0，之后再加上即可。
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}

void ntt(Z y[], int len, int on)
{
    assert((len == (len & -len)) && len);
    constexpr Z g = 3;

    // 位逆序置换
    change(y, len);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
        // wn：当前单位复根的间隔：w^1_h
        Z wn = power(g, (Z::mod() - 1) / h);
        if (on == -1) wn = wn.inv();
        // 合并，共 len / h 次。
        for (int j = 0; j < len; j += h) {
            // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
            // ...
            Z w(1);
            for (int k = j; k < j + h / 2; k++) {
                // 左侧部分和右侧是子问题的解
                Z u = y[k];
                Z t = w * y[k + h / 2];
                // 这就是把两部分分治的结果加起来
                y[k]         = u + t;
                y[k + h / 2] = u - t;
                // 后半个 「step」 中的ω一定和 「前半个」 中的成相反数
                // 「红圈」上的点转一整圈「转回来」，转半圈正好转成相反数
                // 一个数相反数的平方与这个数自身的平方相等
                w = w * wn;
            }
        }
    }
    // 如果是 IDFT，它的逆矩阵的每一个元素不只是原元素取倒数，还要除以长度 len。
    Z iv = Z(len).inv();
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i] = y[i] * iv;
        }
    }
}

/* 多项式乘积
 * n为f和g的最高次和+1
 * 即n = f.len + g.len - 1
 * 注意此处最高次项是长度-1
 * 请保证f和g的长度不小于n
 */
void convolution(Z f[], Z g[], int n)
{
    int lens = 1;
    while (lens < n) lens <<= 1;
    assert(lens < MAXN);
    ntt(f, lens, 1), ntt(g, lens, 1);
    for (int i = 0; i < lens; i++) f[i] = f[i] * g[i];
    ntt(f, lens, -1);
}

/* 多项式求逆(inv)
 * n为f最高次
 * Q(2n) = 2Q(n) - P(n) \cdot Q^2(n)
 */
void polyinv(Z f[], int n)
{
    for (i64 i = 0; i < n; i++) d[i] = 0;
    d[0] = f[0].inv();
    for (int i = 2; i <= n; i <<= 1) {
        for (int j = 0; j < i; j++) b[j] = f[j];
        for (int j = i; j < 2 * i; j++) b[j] = 0;
        for (int j = 0; j < i / 2; j++) c[j] = d[j];
        for (int j = i / 2; j < 2 * i; j++) c[j] = 0;
        ntt(b, i << 1, 1), ntt(c, i << 1, 1);
        for (int j = 0; j < 2 * i; j++) b[j] = b[j] * c[j] * c[j];
        ntt(b, i << 1, -1);
        for (int j = 0; j < i; j++) d[j] = 2ll * d[j] - b[j];
    }
    for (int i = 0; i < n; i++) f[i] = d[i];
}

void polyd(Z f[], int n)
{
    for (int i = 0; i < n - 1; i++) {
        f[i] = f[i + 1] * (i + 1);
    }
    f[n - 1] = 0;
}

void polyint(Z f[], int n)
{
    for (int i = n - 1; i > 0; i--) f[i] = f[i - 1] * Z(i).inv();
    f[0] = 0;
}

/* 多项式求ln
 * G(x) = ln(F(x)) => G'(x) = F'(x) / F(x) => G = int{F'/F}
 */
void polyln(Z f[], int n)
{
    for (int i = 0; i < n; i++) b[i] = f[i];
    polyd(b, n);
    polyinv(f, n);
    for (int i = n; i < 2 * n; i++) f[i] = b[i] = 0;
    // WARNING
    convolution(f, b, 2 * n);
    polyint(b, n);
    for (int i = 0; i < n; i++) f[i] = b[i];
}

/* 多项式求exp
 * exp(x) = 1 + x + x^2/2! ... x^n / n!
 * F_{n} = exp(A) (mod x^n)
 * F_{2n} = F_n \cdot (1 - ln(F_n) + A) (mod x^{2n})
 */
void polyexp(Z f[], int n)
{
    for (int i = 0; i < n; i++) c[i] = 0;
    c[0] = 1;
    for (int i = 2; i <= n; i <<= 1) {
        for (int j = 0; j < i; j++) b[j] = c[j];
        polyln(b, i);
        for (int j = 0; j < i; j++) b[j] = f[j] - b[j];
        b[0] = b[0] + 1;
        for (int j = i; j < 2 * i; j++) b[j] = 0;
        convolution(c, b, 2 * i);
        for (int j = i; j < 2 * i; j++) c[j] = 0;
    }
    for (int i = 0; i < n; i++) f[i] = c[i];
}

/* 多项式快速幂
 * G = F^k => lnG = k lnF => G = exp(k * lnF)
 */
void polyqpow(Z f[], int k, int n)
{
    polyln(f, n);
    for (int i = 0; i < n; i++) f[i] = f[i] * k;
    polyexp(f, n);
}

};  // namespace Poly

using namespace Poly;
constexpr int P = 200001;

void solve()
{
    int slen, tlen, k;
    cin >> slen >> tlen >> k;
    string s;
    cin >> s;
    s = ' ' + s;
    string t;
    cin >> t;
    t = ' ' + t;
    vector<int>       ans(slen + 1);
    vector<bitset<P>> svec(4);
    auto              work = [&](char c) {
        vector<int> tmpsvec(2e5 + 5);
        for (int i = 1; i <= slen; i++) {
            if (s[i] == c) {
                tmpsvec[max(i - k, 1)] += 1;
                tmpsvec[min(i + k + 1, slen + 1)] -= 1;
            }
        }
        for (int i = 2; i <= slen; i++) {
            tmpsvec[i] += tmpsvec[i - 1];
        }
        bitset<P> svec;
        for (int i = 1; i <= slen; i++) {
            if (tmpsvec[i]) {
                svec[i] = 1;
            }
        }
        bitset<P> tvec;
        for (int i = 1; i <= tlen; i++) {
            if (t[i] == c) {
                tvec[i] = 1;
            }
        }
        for (int i = 1; i <= slen - tlen + 1; i++) {
            auto res = svec & tvec;
            ans[i] += res.count();
            svec >>= 1;
        }
    };
    vector<char> cvec = {'A', 'T', 'C', 'G'};
    for (int i = 0; i < 4; i++) {
        work(cvec[i]);
    }
    int anscnt = 0;
    for (int i = 1; i <= slen; i++) {
        if (ans[i] == tlen) {
            anscnt++;
        }
    }
    cout << anscnt << '\n';
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
    int t = 1;
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
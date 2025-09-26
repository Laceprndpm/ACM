#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
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

void flush() { std::cerr.flush(); }

template <class T>
void dbg_wt(const T &val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

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
using ModInt64 = ModIntBase<u64, P>;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const { return m; }

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

    constexpr static void setMod(u32 m) { bt = m; }

    static u32 mod() { return bt.mod(); }

    constexpr u32 val() const { return x; }

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

    constexpr DynModInt &operator/=(const DynModInt &rhs) & { return *this *= rhs.inv(); }

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

    friend constexpr std::ostream &operator<<(std::ostream &os, const DynModInt &a) { return os << a.val(); }

    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs) { return lhs.val() == rhs.val(); }

    friend constexpr std::strong_ordering operator<=>(const DynModInt &lhs, const DynModInt &rhs)
    {
        return lhs.val() <=> rhs.val();
    }

private:
    u32            x;
    static Barrett bt;
};

template <u32 Id>
Barrett       DynModInt<Id>::bt = 998244353;
constexpr u32 P                 = 998244353;
using Z                         = ModInt<P>;
template <u32 x, u32 P>
constexpr ModInt<P> CInv = power(ModInt<P>(x), P - 2);

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
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

template <u32 P>
using MInt = ModInt<P>;

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
template <u32 P>
void change(vector<ModInt<P>> &y)
{
    const int len = y.size();
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

template <u32 P>
struct ntt_traits {
    static constexpr u32 g = 0;
};

template <>
struct ntt_traits<469762049> {
    static constexpr u32 g = 3;
};

template <>
struct ntt_traits<998244353> {
    static constexpr u32 g = 3;
};

template <>
struct ntt_traits<1004535809> {
    static constexpr u32 g = 3;
};

template <u32 P>
void ntt(vector<ModInt<P>> &y, int on)
{
    assert(ntt_traits<P>::g);
    constexpr MInt<P> g   = ntt_traits<P>::g;
    const int         len = y.size();
    assert((len == (len & -len)) && len);
    // 位逆序置换
    change(y);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
        // wn：当前单位复根的间隔：w^1_h
        assert(((P - 1) & (h - 1)) == 0);
        ModInt<P> wn = power(g, (P - 1) / h);
        if (on == -1) wn = wn.inv();
        // 合并，共 len / h 次。
        for (int j = 0; j < len; j += h) {
            // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
            // ...
            ModInt<P> w(1);
            for (int k = j; k < j + h / 2; k++) {
                // 左侧部分和右侧是子问题的解
                ModInt<P> u = y[k];
                ModInt<P> t = w * y[k + h / 2];
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
    ModInt<P> iv = ModInt<P>(len).inv();
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i] = y[i] * iv;
        }
    }
}

template <u32 P>
vector<MInt<P>> convolution(vector<MInt<P>> const &x, vector<MInt<P>> const &y)
{
    assert(x.size() == y.size());
    const u32 n = x.size();
    assert((n & -n) == n);
    constexpr i64      M[3] = {469762049, 998244353, 1004535809};
    vector<MInt<M[0]>> v11(n), v12(n);
    vector<MInt<M[1]>> v21(n), v22(n);
    vector<MInt<M[2]>> v31(n), v32(n);
    memcpy(v11.data(), x.data(), n * sizeof(int));
    memcpy(v21.data(), x.data(), n * sizeof(int));
    memcpy(v31.data(), x.data(), n * sizeof(int));
    memcpy(v12.data(), y.data(), n * sizeof(int));
    memcpy(v22.data(), y.data(), n * sizeof(int));
    memcpy(v32.data(), y.data(), n * sizeof(int));
    ntt(v11, 1), ntt(v12, 1);
    ntt(v21, 1), ntt(v22, 1);
    ntt(v31, 1), ntt(v32, 1);
    for (int i = 0; i < n; i++) {
        v11[i] *= v12[i];
        v21[i] *= v22[i];
        v31[i] *= v32[i];
    }
    ntt(v11, -1);
    ntt(v21, -1);
    ntt(v31, -1);
    constexpr i128  multi = i128(M[0]) * M[1] * M[2];
    constexpr i128  m0    = multi / M[0];
    constexpr i128  m1    = multi / M[1];
    constexpr i128  m2    = multi / M[2];
    vector<MInt<P>> res(n);
    for (int i = 0; i < n; i++) {
        constexpr i128 c0 = m0 * CInv<u32(m0 % M[0]), u32(M[0])>.val();
        constexpr i128 c1 = m1 * CInv<u32(m1 % M[1]), u32(M[1])>.val();
        constexpr i128 c2 = m2 * CInv<u32(m2 % M[2]), u32(M[2])>.val();
        res[i]            = u32((c0 * v11[i].val() + c1 * v21[i].val() + c2 * v31[i].val()) % multi % P);
    }
    return res;
}

template <u32 P>
void dft(vector<MInt<P>> &vec)
{
    ntt(vec, 1);
}

template <u32 P>
void idft(vector<MInt<P>> &vec)
{
    ntt(vec, -1);
}

template <int P = 998244353>
struct Poly : public vector<MInt<P>> {
    using Value = MInt<P>;

    Poly() : vector<Value>() {}

    explicit constexpr Poly(int n) : vector<Value>(n) {}

    explicit constexpr Poly(const vector<Value> &a) : vector<Value>(a) {}

    constexpr Poly(const initializer_list<Value> &a) : vector<Value>(a) {}

    template <class InputIt, class = _RequireInputIter<InputIt>>
    explicit constexpr Poly(InputIt first, InputIt last) : vector<Value>(first, last)
    {
    }

    template <class F>
    explicit constexpr Poly(int n, F f) : vector<Value>(n)
    {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }

    constexpr Poly shift(int k) const
    {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }

    constexpr Poly trunc(int k) const
    {
        Poly f = *this;
        f.resize(k);
        return f;
    }

    constexpr friend Poly operator+(const Poly &a, const Poly &b)
    {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
        return res;
    }

    constexpr friend Poly operator-(const Poly &a, const Poly &b)
    {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
        return res;
    }

    constexpr friend Poly operator-(const Poly &a)
    {
        vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = -a[i];
        }
        return Poly(res);
    }

    constexpr friend Poly operator*(Poly a, Poly b)
    {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        if (a.size() < b.size()) {
            swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        idft(a);
        a.resize(tot);
        return a;
    }

    // 三模数NTT
    // constexpr friend Poly operator*(Poly a, Poly b)
    // {
    //     if (a.size() == 0 || b.size() == 0) {
    //         return Poly();
    //     }
    //     if (a.size() < b.size()) {
    //         swap(a, b);
    //     }
    //     int n = 1, tot = a.size() + b.size() - 1;
    //     while (n < tot) {
    //         n *= 2;
    //     }
    //     // if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
    //     //     Poly c(a.size() + b.size() - 1);
    //     //     for (int i = 0; i < a.size(); i++) {
    //     //         for (int j = 0; j < b.size(); j++) {
    //     //             c[i + j] += a[i] * b[j];
    //     //         }
    //     //     }
    //     //     return c;
    //     // }
    //     a.resize(n);
    //     b.resize(n);
    //     // dft(a);
    //     // dft(b);
    //     // for (int i = 0; i < n; ++i) {
    //     //     a[i] *= b[i];
    //     // }
    //     // idft(a);
    //     auto res = convolution(a, b);
    //     res.resize(tot);
    //     return Poly{res};
    // }

    constexpr friend Poly operator*(Value a, Poly b)
    {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }

    constexpr friend Poly operator*(Poly a, Value b)
    {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }

    constexpr friend Poly operator/(Poly a, Value b)
    {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] /= b;
        }
        return a;
    }

    constexpr Poly &operator+=(Poly b) { return (*this) = (*this) + b; }

    constexpr Poly &operator-=(Poly b) { return (*this) = (*this) - b; }

    constexpr Poly &operator*=(Poly b) { return (*this) = (*this) * b; }

    constexpr Poly &operator*=(Value b) { return (*this) = (*this) * b; }

    constexpr Poly &operator/=(Value b) { return (*this) = (*this) / b; }

    constexpr Poly deriv() const
    {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = (i + 1) * (*this)[i + 1];
        }
        return res;
    }

    constexpr Poly integr() const
    {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = (*this)[i] / (i + 1);
        }
        return res;
    }

    constexpr Poly inv(int m) const
    {
        Poly x{(*this)[0].inv()};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }

    constexpr Poly log(int m) const { return (deriv() * inv(m)).integr().trunc(m); }

    constexpr Poly exp(int m) const
    {
        Poly x{1};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }

    constexpr Poly pow(int k, int m) const
    {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return Poly(m);
        }
        Value v = (*this)[i];
        auto  f = shift(-i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }

    constexpr Poly sqrt(int m) const
    {
        Poly x{1};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
        }
        return x.trunc(m);
    }

    constexpr Poly mulT(Poly b) const
    {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }

    // 多项式求值
    constexpr vector<Value> eval(vector<Value> x) const
    {
        if (this->size() == 0) {
            return vector<Value>(x.size(), 0);
        }
        const int     n = max(x.size(), this->size());
        vector<Poly>  q(4 * n);
        vector<Value> ans(x.size());
        x.resize(n);
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int  m   = (l + r) / 2;
                Poly tmp = num.mulT(q[2 * p + 1]);
                tmp.resize(m - l);
                work(2 * p, l, m, tmp);
                tmp = num.mulT(q[2 * p]);
                tmp.resize(r - m);
                work(2 * p + 1, m, r, tmp);
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

using PolyZ = Poly<P>;

// floor(p / i) * i + p % i == p
// floor(p / i) * i + p % i == 0 (mod p)
// inv[i] == -inv[p % i] * floor(p / i)

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    auto   zip   = [m](int x, int y) { return y * (2 * m) + x; };  // [0, 2 * n * m - 1]
    auto   unzip = [m](i64 c) -> pair<int, int> { return pair<int, int>(c % (2 * m), c / (2 * m)); };
    int    x = 0, y = 0;
    int    mx_x = 0, mx_y = 0, mn_x = 0, mn_y = 0;
    string s;
    cin >> s;
    vector<vector<int>> vis(2 * n, vector<int>(2 * m));
    for (char c : s) {
        switch (c) {
            case 'U': y++; break;
            case 'D': y--; break;
            case 'L': x--; break;
            case 'R': x++; break;
        }
        mx_x = max(mx_x, x);
        mn_x = min(mn_x, x);
        mx_y = max(mx_y, y);
        mn_y = min(mn_y, y);
    }
    if (max(mx_x, -mn_x) >= m || max(mx_y, -mn_y) >= n) {
        if (k == 0) {
            cout << n * m << '\n';
        } else {
            cout << 0 << '\n';
        }
        return;
    }
    vector<vector<int>> debvec(2 * n, vector<int>(2 * m));
    for (int iy = -mn_y; iy < n - mx_y; iy++) {
        for (int ix = -mn_x; ix < m - mx_x; ix++) {
            debvec[iy][ix] = 1;
        }
    }
    dbg(debvec);
    i64                 fianlans = 0;
    int                 death    = (n - mx_y + mn_y) * (m - mx_x + mn_x) - k;
    vector<vector<int>> out(n, vector<int>(m));
    for (int iy = 0; iy < n; iy++) {
        for (int ix = 0; ix < m; ix++) {
            auto cp  = debvec;
            int  bgx = ix, bgy = iy;
            int  ans = 0;
            ans += cp[bgy][bgx];
            cp[bgy][bgx] = 0;
            for (char c : s) {
                switch (c) {
                    case 'U': bgy--; break;
                    case 'D': bgy++; break;
                    case 'L': bgx++; break;
                    case 'R': bgx--; break;
                }
                if (bgx < 0 || bgy < 0) continue;
                ans += cp[bgy][bgx];
                cp[bgy][bgx] = 0;
            }
            out[iy][ix] = ans;
            if (ans == death) fianlans++;
        }
    }
    cout << fianlans << '\n';
    dbg(out);
}

// out =
// [
//   [1, 2, 3, 2, 1, 0, 0, 0, 0, 0],
//   [2, 4, 5, 3, 1, 0, 0, 0, 0, 0],
//   [2, 4, 4, 2, 0, 0, 0, 0, 0, 0],
//   [1, 2, 2, 1, 0, 0, 0, 0, 0, 0],
//   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
//   [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
// ]

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
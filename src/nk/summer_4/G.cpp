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

template <class Info>
struct SegmentTree {
    int          n;
    vector<Info> info;

    SegmentTree() : n(0) {}

    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    SegmentTree(vector<T> init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(vector(n_, v_));
    }

    template <class T>
    void init(vector<T> init_)
    {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }

    void pull(int p)
    {
        info[p] = info[2 * p] + info[2 * p + 1];
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }

    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findFirst(int l, int r, F &&pred)
    {
        return findFirst(1, 0, n, l, r, pred);
    }

    template <class F>
    int findLast(int p, int l, int r, int x, int y, F &&pred)
    {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m   = (l + r) / 2;
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }

    template <class F>
    int findLast(int l, int r, F &&pred)
    {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Info {
    int x;

    Info() : x(0) {}

    Info(int _x) : x(_x) {}
};

Info operator+(const Info &a, const Info &b)
{
    Info c;
    c.x = min(a.x, b.x);
    return c;
}

void solve()
{
    // (( (xx()()) )) -> 0.75 * ()(()())
    // 1 -1 1 -1
    //
    // ((()(()())))
    // for left in range n
    // C(prefix, left)
    //
    // 1 1 1 -1 1 1 -1 1 -1 -1 -1 -1
    // 1 2 3  2 3 4  3 4  3  2  1  0
    // 如果st不混淆，s+t是否一定不混淆？
    // (?+?) x
    // 如果st混淆，s+t是否一定混淆？
    // ✔
    // 如果s混
    // 定义：一个合法的括号序列是独立的
    //
    // （每个(的前缀和为0||每个)的后缀和为0）&&所有(在)前，充分必要
    //
    // 1 2 1 0
    // ( ( ) )
    // ( ? ? )
    //
    // 交换操作相当于什么？
    // 对于i_j区间，使得前缀和在[i, j)上-2（因为不仅仅失去了一个+1,还多了一个-1）,而前缀和始终不能<0
    //
    //
    //
    string s;
    cin >> s;
    int         n = len(s);
    vector<int> prefix(n + 1);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i];
        if (s[i] == '(') {
            prefix[i + 1]++;
        } else {
            prefix[i + 1]--;
        }
    }
    vector<int> cnt_right(n + 1);
    vector<int> cnt_left(n + 1);
    for (int i = 0; i < n; i++) {
        cnt_right[i + 1] = cnt_right[i];
        cnt_left[i + 1]  = cnt_left[i];
        if (s[i] == ')')
            cnt_right[i + 1]++;
        else
            cnt_left[i + 1]++;
    }
    SegmentTree<Info> seg(prefix);

    auto f = [](Info x) -> bool {
        return x.x <= 1;
    };
    Z ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') continue;
        // prefix[i + 1, fi_r] <= 1
        // r > fi_r - 1
        // r >= fi_r
        int fi_r    = seg.findFirst(i + 1, n, f) - 1 + 1;
        Z   cur_ans = power(Z(2), cnt_left[i]);
        cur_ans *= (power(Z(2), cnt_right[n] - cnt_right[fi_r]) - 1);
        ans += cur_ans;
    }
    ans += power(Z(2), n / 2 + 1);
    ans -= 1;
    ans /= power(Z(2), n);
    cout << ans << '\n';
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
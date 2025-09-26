#include <algorithm>
#include <array>
#include <cassert>
#include <cstring>
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

constexpr i64 P = 1e9 + 7;
using Z         = ModInt<P>;

constexpr int N = 120;

Z   f[N + 2][N + 2];
i64 n, W, H;
i64 zero;
Z   con = 1;

void init()
{
    memset(f, 0, sizeof(f));
    zero    = 0;
    con     = 1;
    f[0][0] = 1;
}

pair<Z, Z> calc(i64 WH, i64 wh, i64 x)  // A为{W, H}，c为对应的wi, hi, x为起始点
{
    Z p = 0, q = 0;
    if (x < WH - wh) {
        q += 1;
    } else {
        p += WH - wh;
    }
    if (x < wh) {
        ;
    } else {
        p += wh;
        q -= 1;
    }
    p /= (WH - wh);
    q /= (WH - wh);
    return {p, q};
}

void add(pair<Z, Z> fx, pair<Z, Z> fy)
{
    Z arr[2][2] = {{1 - fx.fi * fy.fi, -fx.fi * fy.se}, {-fx.se * fy.fi, -fx.se * fy.se}};
    if (arr[0][0] == 0) {
        zero++;
        return;
    }
    for (int i = n; i >= 0; i--) {
        for (int j = n; j >= 0; j--) {
            f[i + 1][j + 0] += f[i][j] * arr[1][0];
            f[i + 0][j + 1] += f[i][j] * arr[0][1];
            f[i + 1][j + 1] += f[i][j] * arr[1][1];
        }
    }
    if (arr[0][0] != 1) {
        con *= arr[0][0];
    }
}

void rem(pair<Z, Z> fx, pair<Z, Z> fy)
{
    Z arr[2][2] = {{1 - fx.fi * fy.fi, -fx.fi * fy.se}, {-fx.se * fy.fi, -fx.se * fy.se}};
    if (arr[0][0] == 0) {
        zero--;
        return;
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            f[i + 1][j + 0] -= f[i][j] * arr[1][0];
            f[i + 0][j + 1] -= f[i][j] * arr[0][1];
            f[i + 1][j + 1] -= f[i][j] * arr[1][1];
        }
    }
    if (arr[0][0] != 1) {
        con /= arr[0][0];
    }
}

void solve()
{
    cin >> n >> W >> H;

    W *= 2, H *= 2;
    vector<i64> wi(n), hi(n);
    for (int i = 0; i < n; i++) {
        cin >> wi[i] >> hi[i];
        wi[i] *= 2;
        hi[i] *= 2;
    }
    vector<i64> acx{0, W / 2}, acy{0, H / 2};
    for (int i = 0; i < n; i++) {
        acx.pb(min(wi[i], W - wi[i]));
        acy.pb(min(hi[i], H - hi[i]));
    }
    sor(acx), sor(acy);
    acx.erase(unique(all(acx)), acx.end());
    acy.erase(unique(all(acy)), acy.end());
    const int           lenx = sz(acx), leny = sz(acy);
    vector<vector<int>> acid(leny);
    for (int i = 0; i < n; i++) {
        const int id = lower_bound(all(acy), min(hi[i], H - hi[i])) - acy.begin();
        acid[id].pb(i);
    }
    Z ans = 0;
    for (int s = 0; s < sz(acx) - 1; s++) {
        const i64 x0 = acx[s], x1 = acx[s + 1];
        init();
        for (int i = 0; i < n; i++) {
            const auto a = calc(W, wi[i], x0);  // 扫的x,所以x可以确定
            const auto b = calc(H, hi[i], 0);   // 从0开始
            add(a, b);
        }
        for (int t = 0; t < sz(acy) - 1; t++) {
            const i64 y0 = acy[t], y1 = acy[t + 1];
            for (const int i : acid[t]) {
                const auto a  = calc(W, wi[i], x0);
                const auto b  = calc(H, hi[i], 0);
                const auto bb = calc(H, hi[i], y0);
                rem(a, b);
                add(a, bb);
            }
            vector<Z> inteX(n + 1), inteY(n + 1);
            {
                Z a = 1, b = 1;
                for (int k = 0; k <= n; k++) {
                    a *= x1, b *= x0;
                    inteX[k] = (b - a) / (k + 1);
                }
            }
            {
                Z a = 1, b = 1;
                for (int k = 0; k <= n; k++) {
                    a *= y1, b *= y0;
                    inteY[k] = (b - a) / (k + 1);
                }
            }
            if (zero) continue;
            Z sum = 0;
            for (int k = 0; k <= n; ++k)
                for (int l = 0; l <= n; ++l) sum += f[k][l] * inteX[k] * inteY[l];
            ans += sum * con;
        }
    }
    ans = Z(W / 2) * (H / 2) - ans;

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
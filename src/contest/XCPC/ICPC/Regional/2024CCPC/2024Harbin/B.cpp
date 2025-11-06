#include <cassert>
#include <cmath>
#include <iostream>
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

using T = i64;  // 全局数据类型

constexpr T      eps = 0;
constexpr T      INF = numeric_limits<T>::max();
constexpr double PI  = 3.1415926535897932384l;

struct Point {
    T x, y;

    bool operator==(const Point &a) const { return (abs(x - a.x) <= eps && abs(y - a.y) <= eps); }

    bool operator<(const Point &a) const
    {
        if (abs(x - a.x) <= eps) return y < a.y - eps;
        return x < a.x - eps;
    }

    bool operator>(const Point &a) const { return !(*this < a || *this == a); }

    Point operator+(const Point &a) const { return {x + a.x, y + a.y}; }

    Point operator-(const Point &a) const { return {x - a.x, y - a.y}; }

    Point operator-() const { return {-x, -y}; }

    Point operator*(const T k) const { return {k * x, k * y}; }

    Point operator/(const T k) const { return {x / k, y / k}; }

    T operator*(const Point &a) const { return x * a.x + y * a.y; }  // 点积

    T operator^(const Point &a) const { return x * a.y - y * a.x; }  // 叉积，注意优先级

    int toleft(const Point &a) const
    {
        const auto t = (*this) ^ a;
        return (t > eps) - (t < -eps);
    }  // to-left 测试

    T len2() const { return (*this) * (*this); }  // 向量长度的平方

    T dis2(const Point &a) const { return (a - (*this)).len2(); }  // 两点距离的平方

    int quad() const  // 象限判断 0:原点 1:x轴正 2:第一象限 3:y轴正 4:第二象限 5:x轴负 6:第三象限 7:y轴负 8:第四象限
    {
        if (abs(x) <= eps && abs(y) <= eps) return 0;
        if (abs(y) <= eps) return x > eps ? 1 : 5;
        if (abs(x) <= eps) return y > eps ? 3 : 7;
        return y > eps ? (x > eps ? 2 : 4) : (x > eps ? 8 : 6);
    }

    // 必须用浮点数
    // T len() const { return sqrtl(len2()); }  // 向量长度
};

struct Polygon {
    vector<Point> p;  // 以逆时针顺序存储

    size_t nxt(const size_t i) const { return i == p.size() - 1 ? 0 : i + 1; }

    size_t pre(const size_t i) const { return i == 0 ? p.size() - 1 : i - 1; }

    T area() const
    {
        T sum = 0;
        for (size_t i = 0; i < p.size(); i++) sum += p[i] ^ p[nxt(i)];
        return sum;
    }
};

struct Convex : Polygon {
    // 旋转卡壳
    // 例：凸多边形的直径的平方
    T rotcaliper() const
    {
        const auto &p = this->p;
        if (p.size() == 1) return 0;
        if (p.size() == 2) return p[0].dis2(p[1]);
        const auto area = [](const Point &u, const Point &v, const Point &w) { return (w - u) ^ (w - v); };
        T          ans  = 0;
        for (size_t i = 0, j = 1; i < p.size(); i++) {
            const auto nxti = this->nxt(i);
            ans             = max({ans, p[j].dis2(p[i]), p[j].dis2(p[nxti])});
            while (area(p[this->nxt(j)], p[i], p[nxti]) >= area(p[j], p[i], p[nxti])) {
                j   = this->nxt(j);
                ans = max({ans, p[j].dis2(p[i]), p[j].dis2(p[nxti])});
            }
        }
        return ans;
    }
};

// 旋转卡壳
// 例：凸多边形的直径的平方
T rotcaliper2(Convex outer, Convex inter)
{
    assert(outer.p.size() >= 3);
    assert(inter.p.size() != 0);
    const auto &p    = outer.p;
    const auto &q    = inter.p;
    const auto  area = [](const Point &u, const Point &v, const Point &w) { return (w - u) ^ (w - v); };
    T           ans  = INF;
    for (size_t i = 0, j = 0; i < p.size(); i++) {
        const auto nxti = outer.nxt(i);
        ans             = min({ans, area(q[j], p[i], p[nxti])});
        while (area(q[inter.nxt(j)], p[i], p[nxti]) < area(q[j], p[i], p[nxti])) {
            j   = inter.nxt(j);
            ans = min({ans, area(q[j], p[i], p[nxti])});
        }
    }
    return ans;
}

Convex convexhull(vector<Point> p)

{
    vector<Point> st;
    if (p.empty()) return Convex{st};
    if (p.size() == 1) return Convex{p};
    sort(p.begin(), p.end());
    const auto check = [](const vector<Point> &st, const Point &u) {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).toleft(u - back1) <= 0;
    };
    for (const Point &u : p) {
        while (st.size() > 1 && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    size_t k = st.size();
    p.pop_back();
    reverse(p.begin(), p.end());
    for (const Point &u : p) {
        while (st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return Convex{st};
}

void solve()
{
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        int xi, yi;
        cin >> xi >> yi;
        points[i] = {xi, yi};
    }
    sor(points);
    auto con1  = convexhull(points);
    auto con1p = con1.p;
    sor(con1p);
    vector<int> onCon1(n);
    for (int i = 0, j = 0; i < con1p.size(); i++) {
        while (points[j] != con1p[i]) {
            j++;
        }
        onCon1[j] = 1;
    }
    vector<Point> remain;
    for (int i = 0; i < n; i++) {
        if (!onCon1[i]) {
            remain.pb(points[i]);
        }
    }
    if (remain.size() == 0) {
        cout << -1 << '\n';
        return;
    }
    auto con2       = convexhull(remain);
    i64  removearea = rotcaliper2(con1, con2);
    cout << con1.area() - removearea << '\n';
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
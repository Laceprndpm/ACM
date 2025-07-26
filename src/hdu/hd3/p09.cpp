#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
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

template <>
void smart_print(std::ostream &os, const pair<int, int> &val, int indent)
{
    os << '(' << val.fi << ", " << val.se << ')' << '\n';
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

constexpr i64 MOD = 1e9 + 7;

// assume -P <= x < 2P
int jianglynorm(int x)
{
    if (x < 0) {
        x += MOD;
    }
    if (x >= MOD) {
        x -= MOD;
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

    Z(i64 x) : x(jianglynorm(x % MOD)) {}

    int val() const
    {
        return x;
    }

    Z operator-() const
    {
        return Z(jianglynorm(MOD - x));
    }

    Z inv() const
    {
        assert(x != 0);
        return power(*this, MOD - 2);
    }

    Z &operator*=(const Z &rhs)
    {
        x = i64(x) * rhs.x % MOD;
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

template <class Info, class Tag>
struct LazySegmentTree {
    int          n;
    vector<Info> info;
    vector<Tag>  tag;

    LazySegmentTree() : n(0) {}

    LazySegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    template <class T>
    LazySegmentTree(vector<T> init_)
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
        tag.assign(4 << __lg(n), Tag());
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

    void apply(int p, const Tag &v)
    {
        info[p].apply(v);
        tag[p].apply(v);
    }

    void push(int p)
    {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }

    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
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
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }

    void modify2(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1) {
            info[p] = info[p] + v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify2(2 * p, l, m, x, v);
        } else {
            modify2(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }

    void modify2(int p, const Info &v)
    {
        modify2(1, 0, n, p, v);
    }

    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }

    void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
    {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }

    void rangeApply(int l, int r, const Tag &v)
    {
        return rangeApply(1, 0, n, l, r, v);
    }

    void half(int p, int l, int r)
    {
        if (info[p].act == 0) {
            return;
        }
        if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2) {
            apply(p, {-(info[p].min + 1) / 2});
            return;
        }
        int m = (l + r) / 2;
        push(p);
        half(2 * p, l, m);
        half(2 * p + 1, m, r);
        pull(p);
    }

    void half()
    {
        half(1, 0, n);
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
        int m = (l + r) / 2;
        push(p);
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
        int m = (l + r) / 2;
        push(p);
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

    void maintainL(int p, int l, int r, int pre)
    {
        if (info[p].difl > 0 && info[p].maxlowl < pre) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainL(2 * p, l, m, pre);
        pre = max(pre, info[2 * p].max);
        maintainL(2 * p + 1, m, r, pre);
        pull(p);
    }

    void maintainL()
    {
        maintainL(1, 0, n, -1);
    }

    void maintainR(int p, int l, int r, int suf)
    {
        if (info[p].difr > 0 && info[p].maxlowr < suf) {
            return;
        }
        if (r - l == 1) {
            info[p].max  = info[p].maxlowl;
            info[p].maxl = info[p].maxr = l;
            info[p].maxlowl = info[p].maxlowr = -INF;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        maintainR(2 * p + 1, m, r, suf);
        suf = max(suf, info[2 * p + 1].max);
        maintainR(2 * p, l, m, suf);
        pull(p);
    }

    void maintainR()
    {
        maintainR(1, 0, n, -1);
    }
};

struct Tag {
    Z x = 1;

    void apply(const Tag &t) &
    {
        x = x * t.x;
    }
};

struct Info {
    Z x = 0;

    void apply(const Tag &t) &
    {
        this->x = this->x * t.x;
    }
};

Info operator+(const Info &a, const Info &b)
{
    return {a.x + b.x};
}

void solve()
{
    // dp
    // 遍历所有点，dp1为该点前面]所有的线段都被染色的概率，即r <= i都被染色
    // dp2为r <= i都被染色，但当前i < r没有全部染色
    // 若当前点在l <= r内，且
    // [1, 4]
    // dp2[0] = 1
    // 来到1点，对1染色会导致r变成4,则应该直接加到dp2[5]
    // 如果不染色，则只会dp2[1] = dp2[0] * (1 - pi)
    // ...
    // 来到4点，对4染色会导致r变成4,则dp2[5] ++
    //
    // =============================================================
    //
    // 如果不染色，则直接失败，单调栈？
    // [1, 5] [3, 7]
    // [2, 6]
    //
    //==============================================================
    //
    // 设dp_line为染完了所有j条线段
    // 则，当染色第i点时，假如i覆盖了line_l到line_r,可以使得全部转移到后面去？
    //

    //
    int n, m;
    cin >> n >> m;
    vector<int> ai(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    vector<pair<int, int>> line(m + 1);
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        line[i] = {l, r};
    }
    sort(all(line), [](auto a, auto b) {
        if (a.fi == b.fi) return a.se > b.se;
        return a.fi < b.fi;
    });
    vector<pair<int, int>> new_line;
    new_line.reserve(m);
    new_line.pb({0, 0});
    for (int i = 1; i <= m; i++) {
        while (new_line.size() > 1 && new_line.bk.se >= line[i].se) {
            new_line.pop_back();
        }
        new_line.pb(line[i]);
    }
    line = new_line;
    dbg(line);
    m = sz(line) - 1;
    vector<int> prefix_line1(n + 2);
    vector<int> prefix_line2(n + 2);
    for (int i = 1; i <= m; i++) {
        prefix_line1[line[i].se + 1]++;
        prefix_line2[line[i].fi]++;
    }
    for (int i = 1; i <= n; i++) {
        prefix_line1[i] += prefix_line1[i - 1];
        prefix_line2[i] += prefix_line2[i - 1];
    }
    LazySegmentTree<Info, Tag> seg(m + 1);

    seg.modify(0, Info{Z{1}});
    for (int i = 1; i <= n; i++) {
        int l = prefix_line1[i] + 1;
        int r = prefix_line2[i];
        if (l > r) continue;
        auto res1 = seg.rangeQuery(max(l - 1, 0), r);
        res1.x    = res1.x * Z(ai[i]) * Z(700000005);  // 加到r头上
        seg.rangeApply(max(l - 1, 0), r, Tag(1 - Z(ai[i]) * Z(700000005)));
        seg.modify2(r, res1);
    }
    cout << seg.rangeQuery(m, m + 1).x << '\n';
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
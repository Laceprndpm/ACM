// #include <functional>
// #include <iostream>
// #include <vector>

// using namespace std;
// using ll   = long long;
// using u8   = uint8_t;
// using u16  = uint16_t;
// using u32  = uint32_t;
// using i64  = long long;
// using u64  = uint64_t;
// using i128 = __int128;
// using u128 = unsigned __int128;
// using f128 = __float128;

// // vectors
// #define sz(x)   int(size(x))
// #define bg(x)   begin(x)
// #define all(x)  bg(x), end(x)
// #define rall(x) rbegin(x), rend(x)
// #define sor(x)  sort(all(x))
// #define rsz     resize
// #define ins     insert
// #define pb      push_back
// #define eb      emplace_back
// #define ft      front()
// #define bk      back()
// #define mt      make_tuple
// #define fi      first
// #define se      second

// // https://trap.jp/post/1224/
// #define FOR1(a)                       for (i64 _ = 0; _ < i64(a); ++_)
// #define FOR2(i, a)                    for (i64 i = 0; i < i64(a); ++i)
// #define FOR3(i, a, b)                 for (i64 i = a; i < i64(b); ++i)
// #define FOR4(i, a, b, c)              for (i64 i = a; i < i64(b); i += (c))
// #define FOR1_R(a)                     for (i64 i = (a) - 1; i >= i64(0); --i)
// #define FOR2_R(i, a)                  for (i64 i = (a) - 1; i >= i64(0); --i)
// #define FOR3_R(i, a, b)               for (i64 i = (b) - 1; i >= i64(a); --i)
// #define overload4(a, b, c, d, e, ...) e
// #define overload3(a, b, c, d, ...)    d
// #define FOR(...)                      overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
// #define FOR_R(...)                    overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

// constexpr i64 INF = 1e16;

// namespace detail {

// // 检测是否可迭代
// template <class T, class = void>
// struct is_iterable : std::false_type {};

// template <class T>
// struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin())>> : std::true_type {};

// // 递归打印
// template <class T>
// void smart_print(std::ostream &os, const T &val, int indent = 0)
// {
//     if constexpr (is_iterable<T>::value && !std::is_same_v<T, std::string>) {
//         if (indent == 0) {
//             os << '\n';
//         }
//         using element_type   = typename T::value_type;
//         constexpr bool is_2d = is_iterable<element_type>::value;
//         os << (is_2d ? "[\n" : "[");
//         for (auto it = val.begin(); it != val.end();) {
//             if constexpr (is_2d) os << std::string(indent + 2, ' ');
//             smart_print(os, *it, indent + 2);
//             if (++it != val.end()) os << (is_2d ? ",\n" : ", ");
//         }
//         os << (is_2d ? "\n" + std::string(indent, ' ') : "") << "]";
//     } else {
//         os << val;  // 基础类型直接输出
//     }
// }
// }  // namespace detail

// #define GREEN "\033[32m"
// #define RED   "\033[31m"
// #define RESET "\033[0m"

// void flush()
// {
//     std::cerr.flush();
// }

// template <class T>
// void dbg_wt(const T &val)
// {
//     std::cerr << RED;
//     detail::smart_print(std::cerr, val);
//     std::cerr << RESET;
// }

// void print()
// {
//     dbg_wt('\n');
// }

// template <class Head, class... Tail>
// void print(Head &&head, Tail &&...tail)
// {
//     dbg_wt(head);
//     if (sizeof...(Tail)) dbg_wt(' ');
//     print(forward<Tail>(tail)...);
// }

// #if defined(DEBUG)
// #define dbg(...)                                    dbg_IMPL(__VA_ARGS__, dbg6, dbg5, dbg4, dbg3, dbg2,
// dbg1)(__VA_ARGS__) #define dbg_IMPL(_1, _2, _3, _4, _5, _6, NAME, ...) NAME #define dbg1(x) print(#x, "=", (x)),
// flush() #define dbg2(x, y)                                  print(#x, "=", (x), #y, "=", (y)), flush() #define
// dbg3(x, y, z)                               print(#x, "=", (x), #y, "=", (y), #z, "=", (z)), flush() #define dbg4(x,
// y, z, w)                            print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w)), flush() #define
// dbg5(x, y, z, w, v)                         print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=",
// (v)), flush()
// #define dbg6(x, y, z, w, v, u) \
//     print(#x, "=", (x), #y, "=", (y), #z, "=", (z), #w, "=", (w), #v, "=", (v), #u, "=", (u)), flush()
// #else
// #define dbg(...)
// #endif
// template <class Info, class Tag>
// struct LazySegmentTree {
//     int          n;
//     vector<Info> info;
//     vector<Tag>  tag;

//     LazySegmentTree() : n(0) {}

//     LazySegmentTree(int n_, Info v_ = Info())
//     {
//         init(n_, v_);
//     }

//     template <class T>
//     LazySegmentTree(vector<T> init_)
//     {
//         init(init_);
//     }

//     void init(int n_, Info v_ = Info())
//     {
//         init(vector(n_, v_));
//     }

//     template <class T>
//     void init(vector<T> init_)
//     {
//         n = init_.size();
//         info.assign(4 << __lg(n), Info());
//         tag.assign(4 << __lg(n), Tag());
//         function<void(int, int, int)> build = [&](int p, int l, int r) {
//             if (r - l == 1) {
//                 info[p] = init_[l];
//                 return;
//             }
//             int m = (l + r) / 2;
//             build(2 * p, l, m);
//             build(2 * p + 1, m, r);
//             pull(p);
//         };
//         build(1, 0, n);
//     }

//     void pull(int p)
//     {
//         info[p] = info[2 * p] + info[2 * p + 1];
//     }

//     void apply(int p, const Tag &v)
//     {
//         info[p].apply(v);
//         tag[p].apply(v);
//     }

//     void push(int p)
//     {
//         apply(2 * p, tag[p]);
//         apply(2 * p + 1, tag[p]);
//         tag[p] = Tag();
//     }

//     void modify(int p, int l, int r, int x, const Info &v)
//     {
//         if (r - l == 1) {
//             info[p] = v;
//             return;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         if (x < m) {
//             modify(2 * p, l, m, x, v);
//         } else {
//             modify(2 * p + 1, m, r, x, v);
//         }
//         pull(p);
//     }

//     void modify(int p, const Info &v)
//     {
//         modify(1, 0, n, p, v);
//     }

//     Info rangeQuery(int p, int l, int r, int x, int y)
//     {
//         if (l >= y || r <= x) {
//             return Info();
//         }
//         if (l >= x && r <= y) {
//             return info[p];
//         }
//         int m = (l + r) / 2;
//         push(p);
//         return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
//     }

//     Info rangeQuery(int l, int r)
//     {
//         return rangeQuery(1, 0, n, l, r);
//     }

//     void rangeApply(int p, int l, int r, int x, int y, const Tag &v)
//     {
//         if (l >= y || r <= x) {
//             return;
//         }
//         if (l >= x && r <= y) {
//             apply(p, v);
//             return;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         rangeApply(2 * p, l, m, x, y, v);
//         rangeApply(2 * p + 1, m, r, x, y, v);
//         pull(p);
//     }

//     void rangeApply(int l, int r, const Tag &v)
//     {
//         return rangeApply(1, 0, n, l, r, v);
//     }

//     void half(int p, int l, int r)
//     {
//         if (info[p].act == 0) {
//             return;
//         }
//         if ((info[p].min + 1) / 2 == (info[p].max + 1) / 2) {
//             apply(p, {-(info[p].min + 1) / 2});
//             return;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         half(2 * p, l, m);
//         half(2 * p + 1, m, r);
//         pull(p);
//     }

//     void half()
//     {
//         half(1, 0, n);
//     }

//     template <class F>
//     int findFirst(int p, int l, int r, int x, int y, F &&pred)
//     {
//         if (l >= y || r <= x) {
//             return -1;
//         }
//         if (l >= x && r <= y && !pred(info[p])) {
//             return -1;
//         }
//         if (r - l == 1) {
//             return l;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         int res = findFirst(2 * p, l, m, x, y, pred);
//         if (res == -1) {
//             res = findFirst(2 * p + 1, m, r, x, y, pred);
//         }
//         return res;
//     }

//     template <class F>
//     int findFirst(int l, int r, F &&pred)
//     {
//         return findFirst(1, 0, n, l, r, pred);
//     }

//     template <class F>
//     int findLast(int p, int l, int r, int x, int y, F &&pred)
//     {
//         if (l >= y || r <= x) {
//             return -1;
//         }
//         if (l >= x && r <= y && !pred(info[p])) {
//             return -1;
//         }
//         if (r - l == 1) {
//             return l;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         int res = findLast(2 * p + 1, m, r, x, y, pred);
//         if (res == -1) {
//             res = findLast(2 * p, l, m, x, y, pred);
//         }
//         return res;
//     }

//     template <class F>
//     int findLast(int l, int r, F &&pred)
//     {
//         return findLast(1, 0, n, l, r, pred);
//     }

//     void maintainL(int p, int l, int r, int pre)
//     {
//         if (info[p].difl > 0 && info[p].maxlowl < pre) {
//             return;
//         }
//         if (r - l == 1) {
//             info[p].max  = info[p].maxlowl;
//             info[p].maxl = info[p].maxr = l;
//             info[p].maxlowl = info[p].maxlowr = -INF;
//             return;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         maintainL(2 * p, l, m, pre);
//         pre = max(pre, info[2 * p].max);
//         maintainL(2 * p + 1, m, r, pre);
//         pull(p);
//     }

//     void maintainL()
//     {
//         maintainL(1, 0, n, -1);
//     }

//     void maintainR(int p, int l, int r, int suf)
//     {
//         if (info[p].difr > 0 && info[p].maxlowr < suf) {
//             return;
//         }
//         if (r - l == 1) {
//             info[p].max  = info[p].maxlowl;
//             info[p].maxl = info[p].maxr = l;
//             info[p].maxlowl = info[p].maxlowr = -INF;
//             return;
//         }
//         int m = (l + r) / 2;
//         push(p);
//         maintainR(2 * p + 1, m, r, suf);
//         suf = max(suf, info[2 * p + 1].max);
//         maintainR(2 * p, l, m, suf);
//         pull(p);
//     }

//     void maintainR()
//     {
//         maintainR(1, 0, n, -1);
//     }
// };

// struct Tag {
//     i64 x = 0;

//     void apply(const Tag &t) &
//     {
//         x += t.x;
//     }
// };

// struct Info {
//     i64 x = INF;

//     void apply(const Tag &t) &
//     {
//         x += t.x;
//     }
// };

// Info operator+(const Info &a, const Info &b)
// {
//     return {min(a.x, b.x)};
// }

// void solve()
// {
//     int n;
//     cin >> n;
//     vector<int> hi(n + 2);
//     for (int i = 1; i <= n; i++) {
//         cin >> hi[i];
//     }

//     vector<i64> dpseg(n + 3);  // i被直接杀死时，代价最少多少
//     dpseg[n + 1] = 0;
//     dpseg[n + 2] = 0;
//     for (int i = n; i >= 0; i--) {
//         // 1.i + 1被摔死
//         i64 val1 = dpseg[i + 2];
//         val1 += hi[i];
//         val1 += max(hi[i + 1] - i, 0);
//         // 2.i + 1也被直接杀死
//         i64 val2 = dpseg[i + 1];
//         val2 += hi[i];
//         auto val = min(val1, val2);
//         dpseg[i] = val;
//     }
//     cout << dpseg[1] << '\n';
// }

// signed main(signed argc, char **argv)
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);
// #ifdef BATCH
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
//     int t;
//     cin >> t;
//     while (t--) {
//         solve();
//     }
//     return 0;
// }

// /* stuff you should look for
//  * int overflow, array bounds
//  * special cases (n=1?)
//  * do smth instead of nothing and stay organized
//  * WRITE STUFF DOWN
//  * DON'T GET STUCK ON ONE APPROACH
//  */

#include <bits/stdc++.h>
using namespace std;

#define int  long long
#define MAXN 200005
#define INF  (int)1e18

// a[1] 一定是硬打打死的
// a[2] 如果死在 a[1] 前面，摔落伤害就浪费了，最少也要把 a[2] 打成 1 再来
// 把这个序列先削成形如一个数带一个摔落伤害带一堆 1 的形式，然后从后面往前面摔，摔死

// 从后往前做 DP，枚举上一个考虑的点
// dp[i] 表示把 [i,n] 按照上面的策略来做的最小代价，钦定 i 是一个队头

int n, hi[MAXN], dp[MAXN], prefix[MAXN], g[MAXN];

inline void solve()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &hi[i]), prefix[i] = prefix[i - 1] + hi[i], dp[i] = INF;
    g[n + 1] = prefix[n] - (n - 1);
    dp[n] = hi[n], g[n] = dp[n] + prefix[n - 1] - (n - 2);
    for (int i = n - 1, sufmin = INF; i >= 1; i--) {
        // 第一种，i,i+1 都强行打死
        dp[i] = min(dp[i], dp[i + 1] + hi[i]);
        // 第二种，i+1 用 i 摔死
        sufmin = min(sufmin, g[i + 2]);
        // for j in (i + 2), val chmin = 
        dp[i]  = min(dp[i], hi[i] + max(0ll, hi[i + 1] - i) - prefix[i + 1] + i + sufmin);
        g[i]   = dp[i] + prefix[i - 1] - (i - 2);
    }
    printf("%lld\n", dp[1]);
    for (int i = 1; i <= n + 1; i++) dp[i] = g[i] = hi[i] = prefix[i] = 0;
}

signed main()
{
    int testcase;
    scanf("%lld", &testcase);
    while (testcase--) solve();
    return 0;
}
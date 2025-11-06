#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <stack>
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
void smart_print(std::ostream& os, const T& val, int indent = 0)
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
void dbg_wt(const T& val)
{
    std::cerr << RED;
    detail::smart_print(std::cerr, val);
    std::cerr << RESET;
}

void print() { dbg_wt('\n'); }

template <class Head, class... Tail>
void print(Head&& head, Tail&&... tail)
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

void solve()
{
    // 如何查询？暴力的话，每个查询是O(n)
    // 有什么共同点？
    // 每次修改只会修改区间内部的点的权值，但依然是O(n)层的
    // 如果单纯dfs，每次单纯记录翻转，可以二分找到翻转次数，或者说在那一层发生翻转，然后就可以直接在原图查询
    //
    // 5r，p -> w5 - p + 1
    // 4l, p -> w4 - p + 1
    //
    // p -> w4 - (w5 - p + 1) + 1 = w4 - w5 + p;
    // 想复杂了
    //
    int n, q;
    cin >> n;
    vector<i64> wi(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> wi[i];
    }
    cin >> q;
    deque<pair<int, int>> query;
    query.push_back({1, n + 1});
    deque<pair<int, int>> stk;
    stk.push_back({0, INF});
    for (int i = 0; i < q; i++) {
        int cmd;
        cin >> cmd;
        if (cmd == 1 || cmd == 2) {
            int u;
            cin >> u;
            while (query.back().se <= u) {
                query.pop_back();
                stk.pop_back();
            }
            if (query.back().fi == cmd) continue;

            i64 l = 0, r = wi[u];
            if (query.back().fi == 1) {
                r += stk.back().fi;
                l = stk.back().fi;
            } else {
                l += stk.back().se - r;
                r = stk.back().se;
            }
            query.push_back({cmd, u});
            stk.push_back({l, r});
        } else {
            i64 x;
            cin >> x;
            int l = 0, r = stk.size() - 1;
            int ptr = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (stk[mid].fi <= x && x < stk[mid].se) {
                    ptr = mid;
                    l   = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            assert(ptr != -1);
            int level = query[ptr].se;
            i64 ans   = 0;
            x -= stk[ptr].fi;
            if (query[ptr].fi == 1) {
                ans = upper_bound(all(wi), x) - wi.begin();
            } else {
                x   = wi[level] - x - 1;  // 左闭右开
                ans = upper_bound(all(wi), x) - wi.begin();
            }
            ans = n - ans + 1;
            cout << ans << '\n';
        }
    }
}

signed main(signed argc, char** argv)
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
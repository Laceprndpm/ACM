#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
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

vector<int> randmap;
vector<int> remap;

int query(const vector<int>& vec, int x)
{
    cout << "? ";
    cout << x << ' ';
    cout << vec.size() << ' ';
    for (int i : vec) {
        cout << randmap[i] << ' ';
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

mt19937 rd;

void solve()
{
    int n;
    cin >> n;
    randmap = remap = vector<int>(2 * n);
    iota(all(randmap), 0);
    shuffle(randmap.begin() + 1, randmap.end(), rd);
    for (int i = 1; i <= n; i++) {
        remap[randmap[i]] = i;
    }
    int         l = 1, r = 2 * n - 1;
    int         mid = (l + r) / 2;
    vector<int> lft, rgt;
    for (int i = l; i <= mid; i++) {
        lft.pb(i);
    }
    for (int i = mid + 1; i <= r; i++) {
        rgt.pb(i);
    }
    vector<int> lft1, rgt1;
    vector<int> lft2, rgt2;
    for (int i = 1; i <= n; i++) {
        int a, b;
        if ((a = query(lft, i)) && (b = query(rgt, i))) {
            lft1.pb(i);
            rgt1.pb(i);
        } else {
            if (a) {
                lft2.pb(i);
            } else {
                rgt2.pb(i);
            }
        }
    }
    vector<int> cand;
    if (lft1.size() + lft2.size() * 2 != (mid - l + 1)) {
        cand = lft2;
        r    = mid;
    } else {
        cand = rgt2;
        l    = mid + 1;
    }
    auto query_range = [&](int l, int r, int x) {
        vector<int> tmp;
        for (int i = l; i <= r; i++) {
            tmp.pb(i);
        }
        return query(tmp, x);
    };
    for (auto x : cand) {
        int lo = l, hi = r;

        while (lo != hi) {
            int mid = (lo + hi) / 2;
            if (!query_range(lo, mid, x)) {
                lo = mid + 1;
            } else if (!query_range(mid + 1, hi, x)) {
                hi = mid;
            } else {
                break;
            }
        }

        if (lo == hi) {
            cout << "! " << x << endl;
            return;
        }
    }
}

signed main(signed argc, char** argv)
{
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
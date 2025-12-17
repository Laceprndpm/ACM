#include <array>
#include <iostream>
#include <numeric>
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
/**
 * @brief 并查集
 * 0-index
 */

struct DSU {
    int              component;
    std::vector<i64> f, siz;

    DSU() {}

    DSU(int n) : component(n) { init(n); }

    void init(int n)
    {
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
    }

    int find(int x)
    {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        siz[x] += siz[y];
        f[y] = x;
        component--;
        return true;
    }

    i64 size(i64 x) { return siz[find(x)]; }
};

void finish(vector<array<i64, 4>>& ans)
{
    int n = ans.size();
    DSU dsu(n);
    for (int i = 0; i < n; i++) {
        dsu.siz[i] = (ans[i][3] - ans[i][1]) * (ans[i][2] - ans[i][0]);
    }
    auto adj = [](array<i64, 4> a, array<i64, 4> b) {
        if ((a[3] == b[1] || a[1] == b[3]) && !(a[0] >= b[2] || a[2] <= b[0])) {
            return true;
        }
        if ((a[2] == b[0] || a[0] == b[2]) && !(a[1] >= b[3] || a[3] <= b[1])) {
            return true;
        }
        return false;
    };
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (adj(ans[i], ans[j])) {
                dsu.merge(i, j);
            }
        }
    }

    vector<int> vis(n);
    vector<i64> cans;
    for (int i = 0; i < n; i++) {
        if (!vis[dsu.find(i)]) {
            vis[dsu.find(i)] = 1;
            cans.pb(dsu.size(i));
        }
    }
    sor(cans);
    cout << cans.size() << '\n';
    for (i64 i : cans) {
        cout << i << ' ';
    }
    cout << '\n';
}

void solve()
{
    i64 n, X, Y;
    cin >> n >> X >> Y;
    vector<array<i64, 4>> vec;
    vec.pb({0, 0, X, Y});
    while (n--) {
        char c;
        cin >> ws;
        cin >> c;
        i64 a, b;
        cin >> a >> b;
        if (c == 'X') {
            vector<array<i64, 4>> nxt;
            for (auto rec : vec) {
                if ((rec[0] - a) * (rec[2] - a) < 0) {
                    nxt.pb({rec[0], rec[1], a, rec[3]});
                    nxt.pb({a, rec[1], rec[2], rec[3]});
                } else {
                    nxt.pb(rec);
                }
            }
            for (auto& rec : nxt) {
                if (rec[0] < a) {
                    rec[1] -= b;
                    rec[3] -= b;
                } else {
                    rec[1] += b;
                    rec[3] += b;
                }
            }
            vec = std::move(nxt);
        } else {
            vector<array<i64, 4>> nxt;
            for (auto rec : vec) {
                if ((rec[1] - a) * (rec[3] - a) < 0) {
                    nxt.pb({rec[0], rec[1], rec[2], a});
                    nxt.pb({rec[0], a, rec[2], rec[3]});
                } else {
                    nxt.pb(rec);
                }
            }
            for (auto& rec : nxt) {
                if (rec[1] < a) {
                    rec[0] -= b;
                    rec[2] -= b;
                } else {
                    rec[0] += b;
                    rec[2] += b;
                }
            }
            vec = std::move(nxt);
        }
    }
    finish(vec);
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
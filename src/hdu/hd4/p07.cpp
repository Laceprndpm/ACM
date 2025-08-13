#include <bits/stdc++.h>

#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
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
    pair<int, int> x;

    Info() : x(0, 0) {}

    Info(int _x, int _y) : x(_x, _y) {}
};

Info operator+(const Info &a, const Info &b)
{
    if (a.x > b.x) {
        return a;
    } else {
        return b;
    }
}

// 4 : 2 0 2 0 | 1 2 1 0
// 5 : 2 1 2 0 0
// 6 : -1
// n-4 2 1 (n - 7) * '0' 1 3 * '0'
// 0   1 2               n-4

array<int, 4> s1{2, 0, 2, 0};
array<int, 4> s2{1, 2, 1, 0};
array<int, 5> s3{2, 1, 2, 0, 0};

void solve()
{
    // 插入所有非0元素
    // 每次修改
    int n, q;
    cin >> n >> q;
    set<int>    index;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    SegmentTree<Info> seg(n + 1);
    for (int i = 1; i <= n; i++) {
        if (arr[i] != 0) {
            index.ins(i);
        }
    }
    index.ins(n + 1);
    auto check_as_head = [&](int x) -> int {
        assert(x >= 1 && x <= n);
        if (arr[x] == 0) return 0;
        i64 ans = 0;
        if (x + 3 <= n) {
            bool ok1 = 1, ok2 = 1;
            for (int i = 0; i < 4; i++) {
                if (arr[x + i] != s1[i]) {
                    ok1 = 0;
                }
                if (arr[x + i] != s2[i]) {
                    ok2 = 0;
                }
            }
            if (ok1 || ok2) {
                ans = max(ans, 4ll);
            }
        }
        if (x + 4 <= n) {
            bool ok = 1;
            for (int i = 0; i < 5; i++) {
                if (arr[x + i] != s3[i]) {
                    ok = 0;
                }
            }
            if (ok) {
                ans = max(ans, 5ll);
            }
        }

        i64 first_val = arr[x];
        i64 len       = first_val + 4;

        if (x + len - 1 <= n && len >= 7) {
            if (arr[x + 1] == 2 && arr[x + 2] == 1 && arr[x + len - 4] == 1) {
                auto it = index.find(x);
                for (int i = 0; i < 4; i++) {
                    if (*it != n + 1) {
                        it = next(it);
                    }
                }
                if (*it - x >= len) {
                    ans = max(ans, len);
                }
            }
        }
        return ans;
    };
    for (int i = 1; i <= n; i++) {
        seg.modify(i, {check_as_head(i), i});
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, p;
            cin >> x >> p;
            int ori_val = arr[x];

            if (ori_val != 0) {
                auto it = index.find(x);
                assert(*it == x);
                index.erase(it);
            }

            if (p != 0) {
                auto res = index.ins(x);
                assert(res.second);
            }

            arr[x]  = p;
            auto it = index.lower_bound(x);
            for (int i = 0; i < 5; i++) {
                if (*it != n + 1) {
                    int res = check_as_head(*it);
                    seg.modify(*it, {res, *it});
                }
                if (it == index.begin()) {
                    break;
                }
                it = prev(it);
            }
            for (int i = 0; i <= 7; i++) {
                int res = check_as_head(x - i);
                seg.modify(x - i, {res, x - i});
                if (x - i <= 1) break;
            }
        } else {
            int l, r;
            cin >> l >> r;
            r++;
            auto [val, pos] = seg.rangeQuery(l, r).x;
            i64 ans         = val;
            if (pos + val - 1 >= r) {
                ans = seg.rangeQuery(l, pos).x.fi;
            }
            cout << ans << '\n';
        }
    }
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
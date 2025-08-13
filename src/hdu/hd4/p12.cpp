#include <bits/stdc++.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
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

void flush()
{
    std::cerr.flush();
}

template <class T>
void dbg_wt(const T& val)
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

void output(long double x)
{
    static char s[25];
    sprintf(s, "%.4Le", x);
    for (int i : {0, 1, 2, 3, 4, 5, 6, 7})
        printf("%c", s[i]);
    printf("%c", s[strlen(s) - 1]);
}

using myfloat         = double;
constexpr myfloat eps = 1e-6;

auto genFunction = [](const vector<i64>& vec) -> auto {
    auto f = [vec](myfloat x) {
        myfloat ans = 0;
        for (int i = sz(vec) - 1; i >= 0; i--) {
            ans = ans * x + vec[i];
        }
        return ans;
    };

    return f;
};

auto qu = [](const vector<i64>& vec) -> auto {
    vector<i64> tmp(vec.size() - 1);
    for (int i = 1; i < sz(vec); i++) {
        tmp[i - 1] = vec[i] * i;
    }
    auto tmpF = genFunction(tmp);
    auto f    = [tmpF](double x) {
        return sqrtl(tmpF(x) * tmpF(x) + 1);
    };
    return f;
};

myfloat simpson(myfloat l, myfloat r, auto&& f)
{
    myfloat mid = (l + r) / 2;
    return (r - l) * (f(l) + myfloat(4) * f(mid) + f(r)) / 6;  // 辛普森公式
}

myfloat asr(myfloat l, myfloat r, myfloat eps, myfloat ans, int step, auto&& f)
{
    myfloat mid = (l + r) / 2;
    myfloat fl = simpson(l, mid, f), fr = simpson(mid, r, f);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0) return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return asr(l, mid, eps / 2, fl, step - 1, f) + asr(mid, r, eps / 2, fr, step - 1, f);   // 否则分割成两段递归求解
}

myfloat calc(myfloat l, myfloat r, myfloat eps, auto&& f)
{
    return asr(l, r, eps, simpson(l, r, f), 2, f);
}

void solve()
{
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;
    vector<i64> ai(m + 1);
    for (int i = 1; i <= m; i++) {
        scanf("%lld", &ai[i]);
    }

    struct Building {
        i64 wi;
        i64 hi;
        int id;

        bool operator<(Building ot)
        {
            return id < ot.id;
        }
    };

    vector<Building> buildings(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &buildings[i].hi, &buildings[i].wi);
        buildings[i].id = i;
    }

    sort(all(buildings));
    auto    f      = genFunction(ai);
    auto    quxian = qu(ai);
    myfloat ans    = 1e50;
    do {
        myfloat cur_x   = 0;
        myfloat cur_ans = 0;
        for (int i = 1; i < n; i++) {
            myfloat cur_y       = f(cur_x);
            myfloat cur_y_build = cur_y + buildings[i - 1].hi;
            myfloat l = cur_x, r = 1e18;

            while (r - l > (1e-9)) {
                myfloat mid = (l + r) / 2;
                myfloat res = f(mid);  // (mid, res)
                                       // (res - cur_y_build) / (mid - cur_x) == (cur_y_build - Y) / (cur_x - X)
                if ((res - cur_y_build) * (cur_x - X) > (cur_y_build - Y) * (mid - cur_x)
                    && (cur_y - res) * (cur_y - res) + (mid - cur_x) * (mid - cur_x)
                           > max<myfloat>(buildings[i].hi, buildings[i - 1].hi)
                                 * max<myfloat>(buildings[i].hi, buildings[i - 1].hi))

                {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            cur_x = l;
            cur_ans += calc(0, cur_x, eps, quxian) * buildings[i].wi;
        }
        ans = min<myfloat>(ans, cur_ans);
    } while (next_permutation(all(buildings)));

    output(ans);
    putchar('\n');
}

signed main(signed argc, char** argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    int aa;
    a = 1;
    scanf("%d", &t);
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
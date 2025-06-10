#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;

using ll  = long long;
using db  = long double;  // or double, if TL is tight
using str = string;       // yay python!

// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define mp make_pair
#define f  first
#define s  second

#define tcT  template <class T
#define tcTU tcT, class U
// ^ lol this makes everything look weird but I'll try it
tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi  = V<int>;
using vb  = V<bool>;
using vl  = V<ll>;
using vd  = V<db>;
using vs  = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

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

#define lb lower_bound
#define ub upper_bound

tcT > int lwb(const V<T> &a, const T &b)
{
    return int(lb(all(a), b) - bg(a));
}

tcT > int upb(const V<T> &a, const T &b)
{
    return int(ub(all(a), b) - bg(a));
}

// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a)    FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b) - 1; i >= (a); --i)
#define R0F(i, a)    ROF(i, 0, a)
#define rep(a)       F0R(_, a)
#define each(a, x)   for (auto &a : x)

const int MOD = 998244353;  // 1e9+7;
const int MX  = (int)2e5 + 5;
const ll  BIG = 1e18;  // not too close to LLONG_MAX
const db  PI  = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
mt19937   rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
template <class T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x)
{
    return __builtin_popcount(x);
}  // # of bits set

constexpr int bits(int x)
{  // assert(x >= 0); // make C++11 compatible until
   // USACO updates ...
    return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))

constexpr int p2(int x)
{
    return 1 << x;
}

constexpr int msk2(int x)
{
    return p2(x) - 1;
}

ll cdiv(ll a, ll b)
{
    return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up

ll fdiv(ll a, ll b)
{
    return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b)
{
    return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)

tcT > bool ckmax(T &a, const T &b)
{
    return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcTU > T fstTrue(T lo, T hi, U f)
{
    ++hi;
    assert(lo <= hi);  // assuming f is increasing
    while (lo < hi) {  // find first index such that f is true
        T mid = lo + (hi - lo) / 2;
        f(mid) ? hi = mid : lo = mid + 1;
    }
    return lo;
}

tcTU > T lstTrue(T lo, T hi, U f)
{
    --lo;
    assert(lo <= hi);  // assuming f is decreasing
    while (lo < hi) {  // find first index such that f is true
        T mid = lo + (hi - lo + 1) / 2;
        f(mid) ? lo = mid : hi = mid - 1;
    }
    return lo;
}

tcT > void remDup(vector<T> &v)
{  // sort and remove duplicates
    sort(all(v));
    v.erase(unique(all(v)), end(v));
}

tcTU > void safeErase(T &t, const U &u)
{
    auto it = t.find(u);
    assert(it != end(t));
    t.erase(it);
}

inline namespace IO {
#define SFINAE(x, ...)             \
    template <class, class = void> \
    struct x : std::false_type {}; \
    template <class T>             \
    struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is>
struct Reader {
    template <class T>
    void Impl(T &t)
    {
        if constexpr (DefaultI<T>::value)
            is >> t;
        else if constexpr (Iterable<T>::value) {
            for (auto &x : t)
                Impl(x);
        } else if constexpr (IsTuple<T>::value) {
            std::apply(
                [this](auto &...args) {
                    (Impl(args), ...);
                },
                t);
        } else
            static_assert(IsTuple<T>::value, "No matching type for read");
    }

    template <class... Ts>
    void read(Ts &...ts)
    {
        ((Impl(ts)), ...);
    }
};

template <class... Ts>
void re(Ts &...ts)
{
    Reader<cin>{}.read(ts...);
}

#define def(t, args...) \
    t args;             \
    re(args);

template <auto &os, bool debug, bool print_nd>
struct Writer {
    string comma() const
    {
        return debug ? "," : "";
    }

    template <class T>
    constexpr char Space(const T &) const
    {
        return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
    }

    template <class T>
    void Impl(T const &t) const
    {
        if constexpr (DefaultO<T>::value)
            os << t;
        else if constexpr (Iterable<T>::value) {
            if (debug) os << '{';
            int i = 0;
            for (auto &&x : t)
                ((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
            if (debug) os << '}';
        } else if constexpr (IsTuple<T>::value) {
            if (debug) os << '(';
            std::apply(
                [this](auto const &...args) {
                    int i = 0;
                    (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)), ...);
                },
                t);
            if (debug) os << ')';
        } else
            static_assert(IsTuple<T>::value, "No matching type for print");
    }

    template <class T>
    void ImplWrapper(T const &t) const
    {
        if (debug) os << "\033[0;31m";
        Impl(t);
        if (debug) os << "\033[0m";
    }

    template <class... Ts>
    void print(Ts const &...ts) const
    {
        ((Impl(ts)), ...);
    }

    template <class F, class... Ts>
    void print_with_sep(const std::string &sep, F const &f, Ts const &...ts) const
    {
        ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
    }

    void print_with_sep(const std::string &) const
    {
        os << '\n';
    }
};

template <class... Ts>
void pr(Ts const &...ts)
{
    Writer<cout, false, true>{}.print(ts...);
}

template <class... Ts>
void ps(Ts const &...ts)
{
    Writer<cout, false, true>{}.print_with_sep(" ", ts...);
}
}  // namespace IO

inline namespace Debug {
template <typename... Args>
void err(Args... args)
{
    Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
}

template <typename... Args>
void errn(Args... args)
{
    Writer<cerr, true, true>{}.print_with_sep(" | ", args...);
}

void err_prefix(str func, int line, string args)
{
    cerr << "\033[0;31m\u001b[1mDEBUG\033[0m" << " | " << "\u001b[34m" << func << "\033[0m" << ":" << "\u001b[34m"
         << line << "\033[0m" << " - " << "[" << args << "] = ";
}

#ifdef LOCAL
#define dbg(args...)  err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define dbgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
#else
#define dbg(...)
#define dbgn(args...)
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();

// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed()
{
    return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time).count();
}
}  // namespace Debug

inline namespace FileIO {
void setIn(str s)
{
    freopen(s.c_str(), "r", stdin);
}

void setOut(str s)
{
    freopen(s.c_str(), "w", stdout);
}

void setIO(str s = "")
{
    cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
    cout << fixed << setprecision(12);
    // cin.exceptions(cin.failbit);
    // throws exception when do smth illegal
    // ex. try to read letter into int
    if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO

// make sure to intialize ALL GLOBAL VARS between tcs!

/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and
 * updates single elements a[i], taking the difference between the old and new
 * value. Time: Both operations are $O(\log N)$. Status: Stress-tested
 */

tcT > struct BIT {
    int  N;
    V<T> data;

    void init(int _N)
    {
        N = _N;
        data.rsz(N);
    }

    void add(int p, T x)
    {
        for (++p; p <= N; p += p & -p)
            data[p - 1] += x;
    }

    T sum(int l, int r)
    {
        return sum(r + 1) - sum(l);
    }

    T sum(int r)
    {
        T s = 0;
        for (; r; r -= r & -r)
            s += data[r - 1];
        return s;
    }

    int lower_bound(T sum)
    {
        if (sum <= 0) return -1;
        int pos = 0;
        for (int pw = 1 << 25; pw; pw >>= 1) {
            int npos = pos + pw;
            if (npos <= N && data[npos - 1] < sum) pos = npos, sum -= data[pos - 1];
        }
        return pos;
    }
};

void solve(int tc)
{
    def(int, N);
    vpi cities(N);
    re(cities);
    vi distinct_X;
    each(t, cities) distinct_X.pb(t.f);
    remDup(distinct_X);
    BIT<int> bl, br;
    bl.init(sz(distinct_X));
    br.init(sz(distinct_X));
    each(t, cities)
    {
        t.f = lwb(distinct_X, t.f);
        bl.add(t.f, 1);
    }
    sort(all(cities), [](pi a, pi b) {
        return a.s < b.s;
    });
    int k = 0;
    pi  sol{0, 0};
    F0R(i, sz(cities))
    {
        if (i && cities[i - 1].s < cities[i].s) {
            while (2 * (k + 1) <= min(i, sz(cities) - i)) {
                int xl = max(bl.lower_bound(k + 1), br.lower_bound(k + 1));
                int xr = min(br.lower_bound(i - k), bl.lower_bound(sz(cities) - i - k));
                if (xl >= xr) break;
                ++k;
                sol = {distinct_X.at(xl + 1), cities.at(i).s};
            }
        }
        bl.add(cities[i].f, -1);
        br.add(cities[i].f, 1);
    }
    ps(k);
    ps(sol);
}

int main()
{
    setIO();
    int TC;
    re(TC);
    FOR(i, 1, TC + 1) solve(i);
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
#include <bits/stdc++.h>

#include <cassert>
#include <iostream>
#include <stack>
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
constexpr i64 P = 998244353;

// assume -P <= x < 2P
int jianglynorm(int x)
{
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
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

    Z(i64 x) : x(jianglynorm(x % P)) {}

    int val() const
    {
        return x;
    }

    Z operator-() const
    {
        return Z(jianglynorm(P - x));
    }

    Z inv() const
    {
        assert(x != 0);
        return power(*this, P - 2);
    }

    Z &operator*=(const Z &rhs)
    {
        x = i64(x) * rhs.x % P;
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

void solve()
{
    // 容斥x
    //
    // 笛卡尔树
    // 结构难以追踪
    //
    // 区间dp
    // 用单调栈维护的话，每个点有一个l和r
    // 从大到小枚举的话
    // 对于当前的[l,r]，其方案数为枚举l_1和r_1
    // dp[l][r] = dp[l][l_1] * dp[r_1][r]
    //
    int n;
    cin >> n;
    if (n == 0) {
        cout << 1 << '\n';
        return;
    }
    vector<int> arr(n + 1);
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        p[arr[i]] = i;
    }
    vector<int> l_b(n + 1), r_b(n + 1);
    stack<int>  st;
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        l_b[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }
    while (!st.empty()) {
        st.pop();
    }
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        r_b[i] = st.empty() ? n + 1 : st.top();
        st.push(i);
    }
    vector<vector<Z>> dp(n + 2, vector<Z>(n + 2));
    for (int i = n; i >= 1; i--) {
        int pla = p[i];
        int lm = l_b[pla] + 1, rm = r_b[pla] - 1;

        Z suffix = 1;
        Z prefix = 1;

        vector<Z> deqsuf;
        for (int r_i = rm; r_i >= pla; r_i--) {  // 枚举右边界
            suffix += dp[r_i + 1][rm];
            // dp[r_i][rm] += suffix;
            deqsuf.pb(suffix);
        }
        vector<Z> deqpre;
        for (int l_i = lm; l_i <= pla; l_i++) {
            prefix += dp[lm][l_i - 1];
            deqpre.pb(prefix);
        }

        for (int j = 0; j < sz(deqpre); j++) {
            dp[lm][lm + j] += deqpre[j];
            dp[lm + j][rm] += suffix * deqpre[j] - 1;
        }
        Z prefix2 = 0;
        for (int j = pla; j >= lm; j--) {
            prefix2 += dp[lm][j];
            dp[j][rm] += suffix * prefix2 - 1;
        }
        Z suffix2 = 0;
        for (int j = pla; j <= rm; j++) {
            suffix2 += dp[j + 1][rm];
            dp[lm][j] += prefix * suffix2 - 1;
        }
        for (int j = 0; j < sz(deqsuf); j++) {
            dp[rm - j][rm] += deqsuf[j];
        }
        Z ans      = prefix * suffix;
        dp[lm][rm] = ans;
    }
    cout << dp[1][n] << '\n';
}

// 设f(i, x)为i为x的方案数
// f(i1, x) = \sum_{j = 1}^{x} f(i, x)
//
// arr
// 唯一的优化就是在进行范围min时同时对[l_i, mid] [mid, r_i]进行更新
// 因为下一个区间必然完全覆盖上一个区间，因此不需要修改[l_i, r_i]范围
//
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
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt")
using ll        = long long;
using u8        = uint8_t;
using u16       = uint16_t;
using u32       = uint32_t;
using i64       = long long;
using u64       = uint64_t;
using i128      = __int128;
using u128      = unsigned __int128;
using f128      = __float128;
constexpr i64 P = (i64)(1e9 + 7);
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
#define mp      make_pair
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

struct Comb {
    int            n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}

    Comb(int n) : Comb()
    {
        init(n);
    }

    void init(int m)
    {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i]        = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m)
    {
        if (m > n) init(2 * m);
        return _fac[m];
    }

    Z invfac(int m)
    {
        if (m > n) init(2 * m);
        return _invfac[m];
    }

    Z inv(int m)
    {
        if (m > n) init(2 * m);
        return _inv[m];
    }

    Z binom(int n, int m)
    {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

bool is_nim(const vector<int> &o)
{
    int ini = 0;
    for (int i : o) {
        ini ^= i;
    }
    return ini != 0;
}

bool is_abnim(const vector<int> &o)
{
    bool all_one = 1;
    int  ini     = 0;
    for (int i : o) {
        ini ^= i;
    }
    for (int i : o) {
        if (i != 1) {
            all_one = 0;
            break;
        }
    }
    if (all_one && ini == 0) return 1;

    if (!all_one && ini != 0) return 1;
    return 0;
}

void solve()
{
    int n;
    cin >> n;
    i64 a = 0, b = 0, id = 0, trans = 0;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        vector<int> arr(k);
        for (int j = 0; j < k; j++) {
            cin >> arr[j];
        }

        // 1为先手可以必胜,否则后手可以必胜，2为先手可以必败，否则后手可以必败
        // 先->  1 ->后
        // 后-> -1 ->后
        // 先->  2 ->先
        // 后-> -2 ->先
        // 1   2
        // [1 1]
        // [0 0]
        // 有什么是必然的
        // 假设，[1,0]为先手必优
        // 1  -2
        // [0 1]
        // [1 0]
        // 有什么被反转了
        // -1  2
        // [1 0]
        // [0 1]
        // 有什么保持不变
        //
        // -1 -2
        // [0 0]
        // [1 1]

        bool case1 = is_nim(arr);
        bool case2 = is_abnim(arr);
        if (case1) {
            if (case2)
                a++;
            else
                trans++;
        } else {
            if (case2) {
                id++;
            } else {
                b++;
            }
        }
    }
    Z ans = 0;
    if (a == 0 && b == 0) {
        if (trans % 2 == 1) {
            ans = comb.fac(n);
        }
    } else {
        for (int i = 0; i <= trans; i++) {
            if (i % 2 == 0) {  // trans为偶数，则枚举a在最后
                ans += comb.fac(a + b - 1 + trans - i) * a * comb.binom(trans, i) * comb.fac(i) * comb.binom(n, id)
                       * comb.fac(id);
            } else {
                ans += comb.fac(a + b - 1 + trans - i) * b * comb.binom(trans, i) * comb.fac(i) * comb.binom(n, id)
                       * comb.fac(id);
            }
        }
    }
    cout << ans << '\n';
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
    // 最后一个房间为
    // 1 1，即先手必败
    //
    // 1 1 也是先手必败
    //
    // 当异或和为0,即后手可赢
    // 异或和不为0,即先手可赢
    //
    // 5 6
    //
    // 5 6
    //
    // 5 5
    //
    // 1 5
    //
    // 1 0
    //
    // 3
    //
    //
    // A B
    //
    // 1 1 1 m -1
    //
    //
    // 1 1 2 2
    // A 2
    // 1 1 2
    //
    //
    // n * 1 m -1
    //
    // 1为先手可以必胜,否则后手可以必胜，2为先手可以必败，否则后手可以必败
    //

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

// 1  -2
// [0 1]
// [1 0]
//  1  2
// [1 1]
// [0 0]
// -1  2
// [1 0]
// [0 1]
// -1 -2
// [0 0]
// [1 1]
//
// [1 1]   [0 0]   [1 1]
// [0 0] x [1 1] = [0 0]
//
//
//
//
/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
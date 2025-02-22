
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

template <class T>
constexpr T power(T a, i64 b)
{
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p)
{
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <i64 P>
struct MLong {
    i64 x;

    constexpr MLong() : x{}
    {
    }

    constexpr MLong(i64 x) : x{norm(x % getMod())}
    {
    }

    static i64 Mod;

    constexpr static i64 getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(i64 Mod_)
    {
        Mod = Mod_;
    }

    constexpr i64 norm(i64 x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr i64 val() const
    {
        return x;
    }

    explicit constexpr operator i64() const
    {
        return x;
    }

    constexpr MLong operator-() const
    {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MLong inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MLong &operator*=(MLong rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }

    constexpr MLong &operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MLong &operator-=(MLong rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MLong &operator/=(MLong rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr MLong operator*(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MLong operator+(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MLong operator-(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MLong operator/(MLong lhs, MLong rhs)
    {
        MLong res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MLong &a)
    {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MLong lhs, MLong rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MLong lhs, MLong rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
i64 MLong<0LL>::Mod = i64(1E18) + 9;

template <int P>
struct MInt {
    int x;

    constexpr MInt() : x{}
    {
    }

    constexpr MInt(i64 x) : x{norm(x % getMod())}
    {
    }

    static int Mod;

    constexpr static int getMod()
    {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(int Mod_)
    {
        Mod = Mod_;
    }

    constexpr int norm(int x) const
    {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr int val() const
    {
        return x;
    }

    explicit constexpr operator int() const
    {
        return x;
    }

    constexpr MInt operator-() const
    {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr MInt inv() const
    {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr MInt &operator*=(MInt rhs) &
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }

    constexpr MInt &operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt &operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt &operator/=(MInt rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr MInt operator*(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MInt operator+(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MInt operator-(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MInt operator/(MInt lhs, MInt rhs)
    {
        MInt res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream &operator>>(std::istream &is, MInt &a)
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(MInt lhs, MInt rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MInt lhs, MInt rhs)
    {
        return lhs.val() != rhs.val();
    }
};

template <>
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 998244353;
using Z         = MInt<P>;

i64 qpow(i64 n, i64 q, i64 mod = P)
{
    if (q == 0) {
        return 1;
    }
    i64 ans = 1;
    while (q > 0) {
        if (q & 1) {
            ans *= n;
            ans %= mod;
        }
        n *= n;
        n %= mod;
        q >>= 1;
    }
    return ans;
}

// 感觉只和第一个和最后一个元素有关
// a1, a2, a3...an 美丽 等价与 a1 < all an > all
// 假如对于ai，有n个元素小于它，m个元素大于它
// 从小到大枚举，对于a1，只能作为l，可以与a2有0的贡献，与a3有1的贡献，a4有3贡献，与ai有(2^(i-2)-1)的贡献

// 存储1的数量
// 储存每个1后2的数量
// 每对1 3，2^n的贡献
// 1 2 1 2 2 1 2 3
// 2^4 - 1 + 2^3 - 1 + 2^1 - 1
//
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> cnt(4);
    for (int &i : arr) {
        cin >> i;
        // cnt[i]++;
    }
    int       cnt1 = 0;
    vector<Z> twoAfter1(n + 1);
    Z         ans   = 0;
    Z         other = 0;
    Z         base  = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            other += base;
            base = 1;
            cnt1++;
        }
        if (arr[i] == 2) {
            other *= 2;
            base *= 2;
        }
        if (arr[i] == 3) {
            ans += (base + other) - cnt1;
        }
    }
    cout << ans << '\n';
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
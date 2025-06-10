#include <cassert>
#include <cmath>
#include <iostream>
// #include <valarray>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

template <class T>
struct Frac {
    T num;
    T den;

    Frac(T num_, T den_) : num(num_), den(den_)
    {
        if (den < 0) {
            den = -den;
            num = -num;
        }
    }

    Frac() : Frac(0, 1) {}

    Frac(T num_) : Frac(num_, 1) {}

    explicit operator double() const
    {
        return 1. * num / den;
    }

    Frac &operator+=(const Frac &rhs)
    {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        return *this;
    }

    Frac &operator-=(const Frac &rhs)
    {
        num = num * rhs.den - rhs.num * den;
        den *= rhs.den;
        return *this;
    }

    Frac &operator*=(const Frac &rhs)
    {
        num *= rhs.num;
        den *= rhs.den;
        return *this;
    }

    Frac &operator/=(const Frac &rhs)
    {
        num *= rhs.den;
        den *= rhs.num;
        if (den < 0) {
            num = -num;
            den = -den;
        }
        return *this;
    }

    friend Frac operator+(Frac lhs, const Frac &rhs)
    {
        return lhs += rhs;
    }

    friend Frac operator-(Frac lhs, const Frac &rhs)
    {
        return lhs -= rhs;
    }

    friend Frac operator*(Frac lhs, const Frac &rhs)
    {
        return lhs *= rhs;
    }

    friend Frac operator/(Frac lhs, const Frac &rhs)
    {
        return lhs /= rhs;
    }

    friend Frac operator-(const Frac &a)
    {
        return Frac(-a.num, a.den);
    }

    friend bool operator==(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den == rhs.num * lhs.den;
    }

    friend bool operator!=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den != rhs.num * lhs.den;
    }

    friend bool operator<(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den < rhs.num * lhs.den;
    }

    friend bool operator>(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den > rhs.num * lhs.den;
    }

    friend bool operator<=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den <= rhs.num * lhs.den;
    }

    friend bool operator>=(const Frac &lhs, const Frac &rhs)
    {
        return lhs.num * rhs.den >= rhs.num * lhs.den;
    }

    friend std::ostream &operator<<(std::ostream &os, Frac x)
    {
        T g = std::gcd(x.num, x.den);
        x.num /= g;
        x.den /= g;
        if (x.den == 1)
            return os << x.num;
        else
            return os << x.num << '/' << x.den;
    }
};

using Z = long double;

void solve()

{
    int n, k, l;
    cin >> n >> k >> l;
    vector<int> arr(n);  // 接的操作不会让答案变得更糟
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    Z t     = 0;
    Z lastR = 0;
    lastR   = k;
    t       = arr[0];
    for (int i = 1; i < n; i++) {
        Z dis = arr[i] - lastR;
        if (dis - t <= 0) {
            lastR = max(min(lastR + k, arr[i] + t + k), lastR);
        } else {
            Z t_delta = (dis - t) / 2;
            lastR += (dis - t) / 2 + k;
            t += t_delta;
        }
    }
    if (lastR < l) {
        t += l - lastR;
    }
    cout << (int)round(t * 2) << '\n';
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
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#ifndef REMOVE_ME
#include <bits/stdc++.h>
using i64 = long long;
#endif
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

    constexpr MLong() : x{} {}

    constexpr MLong(i64 x) : x{norm(x % getMod())} {}

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

    constexpr MInt() : x{} {}

    constexpr MInt(i64 x) : x{norm(x % getMod())} {}

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

void solve()
{
    i64 n, m, d;
    cin >> n >> m >> d;
    i64            dx = sqrtl(d * d - 1);
    vector<string> board(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> board[i];
        board[i] = ' ' + board[i];
    }
    vector<Z> dp1(m + 2, 1);
    vector<Z> dp2(m + 2, 0);
    vector<Z> dp3(m + 2, 0);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {  // 平移
            if (board[i][j] == 'X') {
                i64 l = max(j - d, 0ll);
                i64 r = min(j + d + 1, m + 1);
                dp3[l] += dp1[j];
                dp3[r] -= dp1[j];
            }
        }

        for (int j = 1; j <= m; j++) {  // 差分
            dp3[j] += dp3[j - 1];
            dp1[j] = dp3[j];
        }
        if (i != n) {
            for (int j = 1; j <= m; j++) {
                if (board[i][j] == 'X') {
                    i64 l = max(j - dx, 0ll);
                    i64 r = min(j + dx + 1, m + 1);
                    dp2[l] += dp1[j];
                    dp2[r] -= dp1[j];
                }
            }

            for (int j = 1; j <= m; j++) {
                dp2[j] += dp2[j - 1];
            }

            swap(dp1, dp2);
            dp2.assign(m + 2, 0);
            dp3.assign(m + 2, 0);
        }
    }

    Z ans = 0;
    for (int j = 1; j <= m; j++) {
        if (board[n][j] == 'X') {
            ans += dp1[j];
        }
    }
    cout << ans << '\n';
}

signed main(int argc, char **argv)
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
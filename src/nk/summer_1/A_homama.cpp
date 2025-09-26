#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &a)
{
    return os << "(" << a.first << ", " << a.second << ")";
};

template <class T>
ostream &operator<<(ostream &os, const vector<T> &as)
{
    const int sz = as.size();
    os << "[";
    for (int i = 0; i < sz; ++i) {
        if (i >= 256) {
            os << ", ...";
            break;
        }
        if (i > 0) {
            os << ", ";
        }
        os << as[i];
    }
    return os << "]";
}

template <class T>
void pv(T a, T b)
{
    for (T i = a; i != b; ++i) cerr << *i << " ";
    cerr << endl;
}

template <class T>
bool chmin(T &t, const T &f)
{
    if (t > f) {
        t = f;
        return true;
    }
    return false;
}

template <class T>
bool chmax(T &t, const T &f)
{
    if (t < f) {
        t = f;
        return true;
    }
    return false;
}

#define COLOR(s) ("\x1b[" s "m")

////////////////////////////////////////////////////////////////////////////////
template <unsigned M_>
struct ModInt {
    static constexpr unsigned M = M_;
    unsigned                  x;

    constexpr ModInt() : x(0U) {}

    constexpr ModInt(unsigned x_) : x(x_ % M) {}

    constexpr ModInt(unsigned long long x_) : x(x_ % M) {}

    constexpr ModInt(int x_) : x(((x_ %= static_cast<int>(M)) < 0) ? (x_ + static_cast<int>(M)) : x_) {}

    constexpr ModInt(long long x_) : x(((x_ %= static_cast<long long>(M)) < 0) ? (x_ + static_cast<long long>(M)) : x_)
    {
    }

    ModInt &operator+=(const ModInt &a)
    {
        x = ((x += a.x) >= M) ? (x - M) : x;
        return *this;
    }

    ModInt &operator-=(const ModInt &a)
    {
        x = ((x -= a.x) >= M) ? (x + M) : x;
        return *this;
    }

    ModInt &operator*=(const ModInt &a)
    {
        x = (static_cast<unsigned long long>(x) * a.x) % M;
        return *this;
    }

    ModInt &operator/=(const ModInt &a) { return (*this *= a.inv()); }

    ModInt pow(long long e) const
    {
        if (e < 0) return inv().pow(-e);
        ModInt a = *this, b = 1U;
        for (; e; e >>= 1) {
            if (e & 1) b *= a;
            a *= a;
        }
        return b;
    }

    ModInt inv() const
    {
        unsigned a = M, b = x;
        int      y = 0, z = 1;
        for (; b;) {
            const unsigned q = a / b;
            const unsigned c = a - q * b;
            a                = b;
            b                = c;
            const int w      = y - static_cast<int>(q) * z;
            y                = z;
            z                = w;
        }
        assert(a == 1U);
        return ModInt(y);
    }

    ModInt operator+() const { return *this; }

    ModInt operator-() const
    {
        ModInt a;
        a.x = x ? (M - x) : 0U;
        return a;
    }

    ModInt operator+(const ModInt &a) const { return (ModInt(*this) += a); }

    ModInt operator-(const ModInt &a) const { return (ModInt(*this) -= a); }

    ModInt operator*(const ModInt &a) const { return (ModInt(*this) *= a); }

    ModInt operator/(const ModInt &a) const { return (ModInt(*this) /= a); }

    template <class T>
    friend ModInt operator+(T a, const ModInt &b)
    {
        return (ModInt(a) += b);
    }

    template <class T>
    friend ModInt operator-(T a, const ModInt &b)
    {
        return (ModInt(a) -= b);
    }

    template <class T>
    friend ModInt operator*(T a, const ModInt &b)
    {
        return (ModInt(a) *= b);
    }

    template <class T>
    friend ModInt operator/(T a, const ModInt &b)
    {
        return (ModInt(a) /= b);
    }

    explicit operator bool() const { return x; }

    bool operator==(const ModInt &a) const { return (x == a.x); }

    bool operator!=(const ModInt &a) const { return (x != a.x); }

    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) { return os << a.x; }
};

////////////////////////////////////////////////////////////////////////////////

constexpr unsigned MO = 1000000007;
using Mint            = ModInt<MO>;

pair<Mint, Mint> calc(Int A, Int c, Int x)
{
    Mint p = 0, q = 0;
    if (x < A - c) {
        q += 1;
    } else {
        p += A - c;
    }
    if (x < c) {
        ;
    } else {
        q -= 1;
        p += c;
    }
    p /= (A - c);
    q /= (A - c);
    return {p, q};
    // Mint p, q;
    // if (2 * c < A) {
    //     if (x < c) {
    //         p = 0;
    //         q = 1;
    //     } else {
    //         p = c;
    //         q = 0;
    //     }
    // } else {
    //     if (x < A - c) {
    //         p = 0;
    //         q = 1;
    //     } else {
    //         p = A - c;
    //         q = 0;
    //     }
    // }
    // p /= (A - c);
    // q /= (A - c);
    // return make_pair(p, q);
}

int         N;
Int         W, H;
vector<Int> wi, hi;

int  zero;
Mint con;
Mint f[130][130];

void init()
{
    zero = 0;
    con  = 1;
    memset(f, 0, sizeof(f));
    f[0][0] += 1;
}

void add(pair<Mint, Mint> a, pair<Mint, Mint> b)
{
    const Mint g[2][2] = {
        {1 - a.first * b.first, 0 - a.first * b.second},
        {0 - a.second * b.first, 0 - a.second * b.second},
    };
    if (g[0][0] == 1) {
        for (int i = N; i >= 0; --i)
            for (int j = N; j >= 0; --j) {
                f[i + 1][j + 1] += f[i][j] * g[1][1];
                f[i + 1][j + 0] += f[i][j] * g[1][0];
                f[i + 0][j + 1] += f[i][j] * g[0][1];
            }
    } else if (g[0][0]) {
        con *= g[0][0];
    } else {
        ++zero;
    }
}

void rem(pair<Mint, Mint> a, pair<Mint, Mint> b)
{
    const Mint g[2][2] = {
        {1 - a.first * b.first, 0 - a.first * b.second},
        {0 - a.second * b.first, 0 - a.second * b.second},
    };
    if (g[0][0] == 1) {
        for (int i = 0; i <= N; ++i)
            for (int j = 0; j <= N; ++j) {
                f[i + 1][j + 1] -= f[i][j] * g[1][1];
                f[i + 1][j + 0] -= f[i][j] * g[1][0];
                f[i + 0][j + 1] -= f[i][j] * g[0][1];
            }
    } else if (g[0][0]) {
        con /= g[0][0];
    } else {
        --zero;
    }
}

int main()
{
    for (; ~scanf("%d%lld%lld", &N, &W, &H);) {
        wi.resize(N);
        hi.resize(N);
        for (int i = 0; i < N; ++i) scanf("%lld%lld", &wi[i], &hi[i]);

        W *= 2;
        H *= 2;
        for (int i = 0; i < N; ++i) {
            wi[i] *= 2;
            hi[i] *= 2;
        }

        vector<Int> xs{0, W / 2}, ys{0, H / 2};
        for (int i = 0; i < N; ++i) {
            xs.push_back(min(wi[i], W - wi[i]));
            ys.push_back(min(hi[i], H - hi[i]));
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        const int xsLen = (int)xs.size() - 1;
        const int ysLen = (int)ys.size() - 1;

        vector<vector<int>> iss(ysLen + 1);
        for (int i = 0; i < N; ++i) {
            const int t = lower_bound(ys.begin(), ys.end(), min(hi[i], H - hi[i])) - ys.begin();
            iss[t].push_back(i);
        }

        Mint ans = 0;
        for (int s = 0; s < xsLen; ++s) {
            const Int x0 = xs[s], x1 = xs[s + 1];
            init();
            for (int i = 0; i < N; ++i) {
                const auto a = calc(W, wi[i], x0);
                const auto b = calc(H, hi[i], 0);
                add(a, b);
            }
            for (int t = 0; t < ysLen; ++t) {
                const Int y0 = ys[t], y1 = ys[t + 1];
                for (const int i : iss[t]) {
                    const auto a  = calc(W, wi[i], x0);
                    const auto b  = calc(H, hi[i], 0);
                    const auto bb = calc(H, hi[i], y0);
                    rem(a, b);
                    add(a, bb);
                }
                vector<Mint> inteX(N + 1), inteY(N + 1);
                for (int k = 0; k <= N; ++k) inteX[k] = (Mint(x1).pow(k + 1) - Mint(x0).pow(k + 1)) / (k + 1);
                for (int l = 0; l <= N; ++l) inteY[l] = (Mint(y1).pow(l + 1) - Mint(y0).pow(l + 1)) / (l + 1);
                if (!zero) {
                    Mint sum = 0;
                    for (int k = 0; k <= N; ++k)
                        for (int l = 0; l <= N; ++l) sum += f[k][l] * inteX[k] * inteY[l];
                    ans += con * sum;
                }
            }
        }
        ans = Mint(W / 2) * Mint(H / 2) - ans;

        printf("%u\n", ans.x);
    }
    return 0;
}

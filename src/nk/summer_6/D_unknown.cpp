#include <bits/stdc++.h>
using i64 = long long;

constexpr i64 P    = 998244353;
constexpr i64 G    = 3;
constexpr i64 MAXN = 1E6;

i64 qpow(i64 a, i64 b)
{
    i64 res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % P;
        }
        b >>= 1;
        a = a * a % P;
    }
    return res;
}

struct Comb {
    Comb(int n) : _fac(n + 1, 1), _inv(n + 1, 1), _invfac(n + 1, 1)
    {
        for (int i = 2; i <= n; ++i) {
            _fac[i]    = _fac[i - 1] * i % P;
            _inv[i]    = (P - P / i) * _inv[P % i] % P;
            _invfac[i] = _inv[i] * _invfac[i - 1] % P;
        }
    }

    i64 fac(int x) { return _fac[x]; }

    i64 invfac(int x) { return _invfac[x]; }

    i64 inv(int x) { return _inv[x]; }

    i64 operator()(int n, int m)
    {
        if (n < m || n < 0 || m < 0) return 0;
        return _fac[n] * _invfac[m] % P * _invfac[n - m] % P;
    }

    std::vector<i64> _fac, _inv, _invfac;  // 阶乘，i的逆元，阶乘的逆元
} comb(MAXN);

struct Poly : std::vector<i64> {
    using std::vector<i64>::vector;

    friend Poly &operator+=(Poly &A, const Poly &B)
    {
        A.resize(std::max(A.size(), B.size()));
        for (int i = 0; i < B.size(); ++i) {
            A[i] = (A[i] + B[i]) % P;
        }
        return A;
    }

    friend Poly &operator-=(Poly &A, const Poly &B)
    {
        A.resize(std::max(A.size(), B.size()));
        for (int i = 0; i < B.size(); ++i) {
            A[i] = (A[i] - B[i] + P) % P;
        }
        return A;
    }

    friend Poly &operator*=(Poly &A, Poly B)
    {
        auto k = A.size() + B.size() - 1;
        auto n = std::bit_ceil(k);
        if (1LL * A.size() * B.size() <= 3 * n * std::bit_width(n)) {
            Poly res(k);
            for (int i = 0; i < A.size(); ++i) {
                for (int j = 0; j < B.size(); ++j) {
                    res[i + j] = (res[i + j] + A[i] * B[j]) % P;
                }
            }
            A = std::move(res);
        } else {
            A.resize(n), B.resize(n);
            NTT(A), NTT(B);
            for (int i = 0; i < n; ++i) {
                A[i] = A[i] * B[i] % P;
            }
            NTT(A, -1);
            std::reverse(A.begin() + 1, A.end());
            i64 invn = P - (P - 1) / n;
            A.resize(k);
            for (auto &x : A) {
                x = x * invn % P;
            }
        }
        return A;
    }

    friend Poly &operator/=(Poly &A, Poly B)
    {
        if (A.size() < B.size()) return A = Poly{0};
        int n = A.size() - B.size() + 1;
        std::reverse(A.begin(), A.end());
        std::reverse(B.begin(), B.end());
        A = A % n * inv(B, n) % n;
        std::reverse(A.begin(), A.end());
        return A;
    }

    friend Poly &operator%=(Poly &A, const Poly &B)
    {
        A = (A - A / B * B) % (B.size() - 1);
        return A;
    }

    friend Poly &operator%=(Poly &A, size_t k)
    {
        A.resize(std::min(A.size(), k));
        return A;
    }

    friend Poly operator+(Poly A, const Poly &B) { return A += B; }

    friend Poly operator-(Poly A, const Poly &B) { return A -= B; }

    friend Poly operator*(Poly A, const Poly &B) { return A *= B; }

    friend Poly operator/(Poly A, const Poly &B) { return A /= B; }

    friend Poly operator%(Poly A, const Poly &B) { return A %= B; }

    friend Poly operator%(Poly A, size_t k) { return A %= k; }

    static Poly derive(const Poly &A)
    {
        if (A.size() <= 1) return Poly{0};
        Poly res(A.size() - 1);
        for (int i = 1; i < A.size(); ++i) {
            res[i - 1] = A[i] * i % P;
        }
        return res;
    }

    static Poly integral(const Poly &A)
    {
        Poly res(A.size() + 1);
        res[1] = A[0];
        for (int i = 2; i <= A.size(); ++i) {
            res[i] = A[i - 1] * comb.inv(i) % P;
        }
        return res;
    }

    static Poly ln(const Poly &A, int n) { return integral(derive(A) % n * inv(A, n) % n) % n; }

    static Poly pow(const Poly &A, i64 k, int n) { return exp(ln(A, n) * Poly{k} % n, n) % n; }

    static Poly inv(const Poly &A, int n)
    {
        Poly res = {qpow(A[0], P - 2)};
        for (int k = 2; k < 2 * n; k <<= 1) {
            res = res * (Poly{2} - A % k * res) % k;
        }
        return res % n;
    }

    static Poly exp(const Poly &A, int n)
    {
        Poly res = {1};
        for (int k = 2; k < 2 * n; k <<= 1) {
            res = res * (A % k - ln(res, k) + Poly{1}) % k;
        }
        return res % n;
    }

    static Poly sqrt(const Poly &A, int n)
    {
        Poly res = {1};
        for (int k = 2; k < 2 * n; k <<= 1) {
            res = (res + A % k * inv(res, k) % k) * Poly{(P + 1) / 2} % k;
        }
        return res % n;
    }

    static Poly ln(const Poly &A) { return ln(A, A.size()); }

    static Poly inv(const Poly &A) { return inv(A, A.size()); }

    static Poly exp(const Poly &A) { return exp(A, A.size()); }

    static Poly sqrt(const Poly &A) { return sqrt(A, A.size()); }

    static Poly pow(const Poly &A, i64 k) { return pow(A, k, A.size()); }

    Poly shift(int k)
    {
        auto A = *this;
        if (k >= 0) {
            A.insert(A.begin(), k, 0);
            return A;
        } else if (A.size() <= -k) {
            return Poly();
        } else {
            return Poly(A.begin() + (-k), A.end());
        }
    }

    static void NTT(std::vector<i64> &A, int opt = 1)
    {
        int n = A.size();
        for (int i = 0, j = 0; i < n; ++i) {
            if (i > j) {
                std::swap(A[i], A[j]);
            }
            for (int k = n >> 1; (j ^= k) < k; k >>= 1);
        }
        init(n);
        for (int i = 1; i < n; i <<= 1) {
            for (int j = 0; j < n; j += (i << 1)) {
                for (int k = j; k < i + j; ++k) {
                    int t    = w[k + i - j] * A[i + k] % P;
                    A[k + i] = (A[k] - t < 0 ? A[k] - t + P : A[k] - t);
                    A[k]     = (A[k] + t >= P ? A[k] + t - P : A[k] + t);
                }
            }
        }
    }

    static void init(int n)
    {
        int m = w.size();
        if (n <= m) return;
        w.resize(n);
        i64 wn    = qpow(G, (P - 1) / n);
        w[n >> 1] = 1;
        for (int i = (n >> 1) + 1; i < n; ++i) {
            w[i] = w[i - 1] * wn % P;
        }
        for (int i = n - 1; i >= m; --i) {
            w[i >> 1] = w[i];
        }
    }

    inline static std::vector<i64> w{1};
};

void solve()
{
    i64 n, m;
    std::cin >> n >> m;
    Poly v(m + 1);
    for (int i = 0; i <= m; ++i) {
        v[i] = comb(i + n - 1, i);
    }
    auto res = Poly::pow(v, n - 1);
    i64  ans = 0;
    for (int i = 0; i <= m; ++i) {
        ans = (ans + res[i]) % P;
    }
    std::cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T = 1;
    // std::cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}

#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
using i64         = long long;
using u64         = unsigned long long;
using u32         = unsigned;
using u128        = unsigned __int128;
constexpr i64 MOD = 1E9 + 7;

template <class T>
constexpr T power(T a, u64 b, T res = 1)
{
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template <u32 P>
constexpr u32 mulMod(u32 a, u32 b)
{
    return u64(a) * b % P;
}

template <u64 P>
constexpr u64 mulMod(u64 a, u64 b)
{
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr i64 safeMod(i64 x, i64 m)
{
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr std::pair<i64, i64> invGcd(i64 a, i64 b)
{
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }

    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;

    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        std::swap(s, t);
        std::swap(m0, m1);
    }

    if (m0 < 0) {
        m0 += b / s;
    }

    return {s, m0};
}

template <std::unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}

    template <std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_ % mod())
    {
    }

    template <std::signed_integral T>
    constexpr ModIntBase(T x_)
    {
        using S = std::make_signed_t<U>;
        S v     = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static U mod()
    {
        return P;
    }

    constexpr U val() const
    {
        return x;
    }

    constexpr ModIntBase operator-() const
    {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr ModIntBase inv() const
    {
        return power(*this, mod() - 2);
    }

    constexpr ModIntBase &operator*=(const ModIntBase &rhs) &
    {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }

    constexpr ModIntBase &operator+=(const ModIntBase &rhs) &
    {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }

    constexpr ModIntBase &operator-=(const ModIntBase &rhs) &
    {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }

    constexpr ModIntBase &operator/=(const ModIntBase &rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, ModIntBase &a)
    {
        i64 i;
        is >> i;
        a = i;
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr std::strong_ordering operator<=>(const ModIntBase &lhs, const ModIntBase &rhs)
    {
        return lhs.val() <=> rhs.val();
    }

private:
    U x;
};

template <u32 P>
using ModInt = ModIntBase<u32, P>;
template <u64 P>
using ModInt64 = ModIntBase<u64, P>;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const
    {
        return m;
    }

    constexpr u32 mul(u32 a, u32 b) const
    {
        u64 z = a;
        z *= b;

        u64 x = u64((u128(z) * im) >> 64);

        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    u32 m;
    u64 im;
};

template <u32 Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}

    template <std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_ % mod())
    {
    }

    template <std::signed_integral T>
    constexpr DynModInt(T x_)
    {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }

    constexpr static void setMod(u32 m)
    {
        bt = m;
    }

    static u32 mod()
    {
        return bt.mod();
    }

    constexpr u32 val() const
    {
        return x;
    }

    constexpr DynModInt operator-() const
    {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }

    constexpr DynModInt inv() const
    {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }

    constexpr DynModInt &operator*=(const DynModInt &rhs) &
    {
        x = bt.mul(x, rhs.val());
        return *this;
    }

    constexpr DynModInt &operator+=(const DynModInt &rhs) &
    {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }

    constexpr DynModInt &operator-=(const DynModInt &rhs) &
    {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }

    constexpr DynModInt &operator/=(const DynModInt &rhs) &
    {
        return *this *= rhs.inv();
    }

    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs)
    {
        lhs -= rhs;
        return lhs;
    }

    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs)
    {
        lhs /= rhs;
        return lhs;
    }

    friend constexpr std::istream &operator>>(std::istream &is, DynModInt &a)
    {
        i64 i;
        is >> i;
        a = i;
        return is;
    }

    friend constexpr std::ostream &operator<<(std::ostream &os, const DynModInt &a)
    {
        return os << a.val();
    }

    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs)
    {
        return lhs.val() == rhs.val();
    }

    friend constexpr std::strong_ordering operator<=>(const DynModInt &lhs, const DynModInt &rhs)
    {
        return lhs.val() <=> rhs.val();
    }

private:
    u32            x;
    static Barrett bt;
};

template <u32 Id>
Barrett DynModInt<Id>::bt = 998244353;

using Z = ModInt<MOD>;

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

// Matrix 类声明
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t                      rows;
    size_t                      cols;

public:
    Matrix(const std::vector<std::vector<T>> &vec);
    Matrix(std::vector<std::vector<T>> &&vec);
    Matrix(Matrix<T> &&other) noexcept;
    Matrix(const Matrix<T> &other);

    std::vector<T>       &operator[](size_t row);
    const std::vector<T> &operator[](size_t row) const;

    size_t getRows() const;
    size_t getCols() const;

    void print() const;

    Matrix<T> &operator=(const Matrix &other);
    Matrix<T> &operator=(Matrix &&other) noexcept;
    bool       operator==(const Matrix &other) const;
    bool       operator!=(const Matrix &other) const;
    Matrix<T>  operator+(const Matrix &other) const;
    Matrix<T>  operator-(const Matrix &other) const;
    Matrix<T>  operator*(const Matrix &other) const;
    Matrix<T>  operator*(const long long k) const;
    Matrix<T>  transpose() const;
    Matrix<T>  power(long long exp);
    Matrix<T>  identityMatrix(size_t size);
};

// Matrix 类实现
template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> &vec)
{
    if (vec.empty() || vec[0].empty()) {
        throw std::invalid_argument("构造矩阵的vector不能为空");
    }

    rows = vec.size();
    cols = vec[0].size();

    for (const auto &row : vec) {
        if (row.size() != cols) {
            throw std::invalid_argument("所有行的元素数量必须相同");
        }
        data.emplace_back(row);
    }
}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> &&vec) : data(std::move(vec))
{
    if (data.empty() || data[0].empty()) {
        throw std::invalid_argument("构造矩阵的vector不能为空");
    }
    rows = data.size();
    cols = data[0].size();
    for (const auto &row : data) {
        if (row.size() != cols) {
            throw std::invalid_argument("所有行的元素数量必须相同");
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix &&other) noexcept : data(std::move(other.data)), rows(other.rows), cols(other.cols)
{
    other.rows = 0;
    other.cols = 0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix &other) : data(other.data), rows(other.rows), cols(other.cols)
{
}

template <typename T>
std::vector<T> &Matrix<T>::operator[](size_t row)
{
    if (row >= rows) {
        throw std::out_of_range("矩阵索引越界");
    }
    return data[row];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](size_t row) const
{
    if (row >= rows) {
        throw std::out_of_range("矩阵索引越界");
    }
    return data[row];
}

template <typename T>
size_t Matrix<T>::getRows() const
{
    return rows;
}

template <typename T>
size_t Matrix<T>::getCols() const
{
    return cols;
}

template <typename T>
void Matrix<T>::print() const
{
    for (const auto &row : data) {
        for (const T &elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix &other)
{
    if (this != &other) {
        data = other.data;
        rows = other.rows;
        cols = other.cols;
    }
    return *this;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(Matrix &&other) noexcept
{
    if (this != &other) {
        data       = std::move(other.data);
        rows       = other.rows;
        cols       = other.cols;
        other.rows = 0;
        other.cols = 0;
    }
    return *this;
}

template <typename T>
bool Matrix<T>::operator==(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols) {
        return false;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
bool Matrix<T>::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("矩阵加法中，两个矩阵的维度必须相同");
    }

    std::vector<std::vector<T>> result(rows, std::vector<T>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("矩阵减法中，两个矩阵的维度必须相同");
    }

    std::vector<std::vector<T>> result(rows, std::vector<T>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &other) const
{
    if (cols != other.rows) {
        throw std::invalid_argument("矩阵乘法中，左矩阵的列数必须等于右矩阵的行数");
    }

    std::vector<std::vector<T>> result(rows, std::vector<T>(other.cols, 0));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                result[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const long long k) const
{
    std::vector<std::vector<T>> result(rows, std::vector<T>(cols));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i][j] = data[i][j] * k;
        }
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const
{
    std::vector<std::vector<T>> result(cols, std::vector<T>(rows));

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = data[i][j];
        }
    }

    return Matrix(result);
}

template <typename T>
Matrix<T> Matrix<T>::power(long long exp)
{
    Matrix result(identityMatrix(this->getRows()));
    Matrix base(*this);

    while (exp) {
        if (exp & 1) {
            result = result * base;
        }
        base = base * base;
        exp /= 2;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::identityMatrix(size_t size)
{
    std::vector<std::vector<T>> id(size, std::vector<T>(size, 0));
    for (size_t i = 0; i < size; ++i) {
        id[i][i] = 1;
    }
    return Matrix(id);
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
    int n;
    cin >> n;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 c, m, k, t;
    cin >> c >> m >> k >> t;
    k %= m;
    c %= m;
    vector<i64> dp1(m), dp2(m);
    dp1[0] = 1;
    for (int i = 0; i < n; i++) {
        arr[i] %= m;
        for (int j = m - 1; j >= 0; j--) {
            dp2[(j + arr[i]) % m] = (dp1[j] + dp1[(j + arr[i]) % m]) % MOD;
        }
        dp1 = dp2;
    }
    dp1[0]--;
    Matrix<Z> mat(vector<vector<Z>>(m, vector<Z>(m, 0)));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            mat[i][(i * j) % m] += dp1[j];
        }
    }
    mat = mat.power(t);
    // vector<i64> cdp(m), ndp(m);
    // cdp[c % m] = 1;
    // for (int i = t; i; i >>= 1) {
    //     if (i & 1) {
    //         for (int j = 0; j < m; j++) {
    //             for (int jj = 0; jj < m; jj++) {
    //                 ndp[(j * jj) % m] = ((cdp[j] * dp1[jj] % MOD) + ndp[(j * jj) % m]) % MOD;
    //             }
    //         }
    //         swap(cdp, ndp);
    //         ndp.assign(ndp.size(), 0);
    //     }
    //     vector<i64> dp2(m);
    //     for (int jj = m - 1; jj >= 0; jj--) {
    //         for (int j = m - 1; j >= 0; j--) {
    //             dp2[(j * jj) % m] = ((dp1[j] * dp1[jj]) % MOD + dp2[(j * jj) % m]) % MOD;
    //         }
    //     }
    //     dp1 = dp2;
    // }
    cout << mat[c % m][k] << '\n';
    return 0;
}

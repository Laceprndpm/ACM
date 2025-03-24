#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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

    constexpr MLong& operator*=(MLong rhs) &
    {
        x = mul(x, rhs.x, getMod());
        return *this;
    }

    constexpr MLong& operator+=(MLong rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MLong& operator-=(MLong rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MLong& operator/=(MLong rhs) &
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

    friend constexpr std::istream& operator>>(std::istream& is, MLong& a)
    {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }

    friend constexpr std::ostream& operator<<(std::ostream& os, const MLong& a)
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
i64 MLong<0LL>::Mod = 1e9 + 7;

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

    constexpr MInt& operator*=(MInt rhs) &
    {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }

    constexpr MInt& operator+=(MInt rhs) &
    {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt& operator-=(MInt rhs) &
    {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt& operator/=(MInt rhs) &
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

    friend constexpr std::istream& operator>>(std::istream& is, MInt& a)
    {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }

    friend constexpr std::ostream& operator<<(std::ostream& os, const MInt& a)
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

constexpr int P = 1e9 + 7;
using Z         = MLong<P>;

// Matrix 类声明
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t                      rows;
    size_t                      cols;

public:
    Matrix(const std::vector<std::vector<T>>& vec);
    Matrix(Matrix&& other) noexcept;
    Matrix(const Matrix& other);

    T&       operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

    size_t getRows() const;
    size_t getCols() const;

    void print() const;

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    bool    operator==(const Matrix& other) const;
    bool    operator!=(const Matrix& other) const;
    Matrix  operator+(const Matrix& other) const;
    Matrix  operator-(const Matrix& other) const;
    Matrix  transpose() const;
    Matrix  operator*(const Matrix& other) const;
};

// Matrix 类实现
template <typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec)
{
    if (vec.empty() || vec[0].empty()) {
        throw std::invalid_argument("构造矩阵的vector不能为空");
    }

    rows = vec.size();
    cols = vec[0].size();

    for (const auto& row : vec) {
        if (row.size() != cols) {
            throw std::invalid_argument("所有行的元素数量必须相同");
        }
        data.emplace_back(row);
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept : data(std::move(other.data)), rows(other.rows), cols(other.cols)
{
    other.rows = 0;
    other.cols = 0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : data(other.data), rows(other.rows), cols(other.cols)
{
}

template <typename T>
T& Matrix<T>::operator()(size_t row, size_t col)
{
    if (row >= rows || col >= cols) {
        throw std::out_of_range("矩阵索引越界");
    }
    return data[row][col];
}

template <typename T>
const T& Matrix<T>::operator()(size_t row, size_t col) const
{
    if (row >= rows || col >= cols) {
        throw std::out_of_range("矩阵索引越界");
    }
    return data[row][col];
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
    for (const auto& row : data) {
        for (const T& elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other)
{
    if (this != &other) {
        data = other.data;
        rows = other.rows;
        cols = other.cols;
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) noexcept
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
bool Matrix<T>::operator==(const Matrix& other) const
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
bool Matrix<T>::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const
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
Matrix<T> Matrix<T>::operator-(const Matrix& other) const
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
Matrix<T> Matrix<T>::operator*(const Matrix& other) const
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

// SquadMatrix 类声明
template <typename T>
class SquadMatrix : public Matrix<T> {
public:
    using Matrix<T>::operator=;
    using Matrix<T>::operator*;
    using Matrix<T>::operator+;
    using Matrix<T>::operator-;
    using Matrix<T>::operator==;
    using Matrix<T>::operator!=;
    SquadMatrix(const std::vector<std::vector<T>>& vec);

    SquadMatrix power(long long exp);

private:
    static SquadMatrix identityMatrix(size_t size);
};

// SquadMatrix 类实现
template <typename T>
SquadMatrix<T>::SquadMatrix(const std::vector<std::vector<T>>& vec) : Matrix<T>(vec)
{
    if (this->getRows() != this->getCols()) {
        throw std::invalid_argument("不是方阵");
    }
}

template <typename T>
SquadMatrix<T> SquadMatrix<T>::power(long long exp)
{
    SquadMatrix result(identityMatrix(this->getRows()));
    SquadMatrix base(*this);

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
SquadMatrix<T> SquadMatrix<T>::identityMatrix(size_t size)
{
    std::vector<std::vector<T>> id(size, std::vector<T>(size, 0));
    for (size_t i = 0; i < size; ++i) {
        id[i][i] = 1;
    }
    return SquadMatrix(id);
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    i64 q;
    cin >> n >> q;
    vector<vector<Z>> mat(n, vector<Z>(n));
    for (auto& i : mat) {
        for (Z& j : i) {
            cin >> j;
        }
    }
    SquadMatrix<Z> m(mat);
    m.power(q).print();
    return 0;
}
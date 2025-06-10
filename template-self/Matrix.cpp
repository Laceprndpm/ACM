// Matrix 类声明
#include <cassert>
#include <vector>

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
    // if (rows != other.rows || cols != other.cols) {
    //     throw std::invalid_argument("矩阵加法中，两个矩阵的维度必须相同");
    // }
    assert(rows == other.rows && cols == other.cols);

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
    // if (rows != other.rows || cols != other.cols) {
    //     throw std::invalid_argument("矩阵减法中，两个矩阵的维度必须相同");
    // }
    assert(rows == other.rows && cols == other.cols);
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
    // if (cols != other.rows) {
    //     throw std::invalid_argument("矩阵乘法中，左矩阵的列数必须等于右矩阵的行数");
    // }
    assert(cols == other.rows);

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
    assert(getCols() == getRows());
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
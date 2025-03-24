#ifndef REMOVE_ME
#include <bits/stdc++.h>
#endif

// Matrix 类声明
template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t                      rows;
    size_t                      cols;

public:
    Matrix(const std::vector<std::vector<T>>& vec);
    Matrix(Matrix<T>&& other) noexcept;
    Matrix(const Matrix<T>& other);

    T&       operator[](size_t row, size_t col);
    const T& operator[](size_t row, size_t col) const;

    size_t getRows() const;
    size_t getCols() const;

    void print() const;

    Matrix<T>& operator=(const Matrix& other);
    Matrix<T>& operator=(Matrix&& other) noexcept;
    bool       operator==(const Matrix& other) const;
    bool       operator!=(const Matrix& other) const;
    Matrix<T>  operator+(const Matrix& other) const;
    Matrix<T>  operator-(const Matrix& other) const;
    Matrix<T>  operator*(const Matrix& other) const;
    Matrix<T>  operator*(const long long k) const;
    Matrix<T>  transpose() const;
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
T& Matrix<T>::operator[](size_t row, size_t col)
{
    if (row >= rows || col >= cols) {
        throw std::out_of_range("矩阵索引越界");
    }
    return data[row][col];
}

template <typename T>
const T& Matrix<T>::operator[](size_t row, size_t col) const
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

// SquadMatrix 类声明
template <typename T>
class SquadMatrix : public Matrix<T> {
public:
    using Matrix<T>::operator[];
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

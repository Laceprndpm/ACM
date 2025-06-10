#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t                      rows;
    size_t                      cols;

public:
    // 构造函数，使用二维vector来初始化矩阵
    Matrix(const std::vector<std::vector<T>>& vec)
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
            data.emplace__back(row);
        }
    }

    // 访问矩阵的元素
    T& operator()(size_t row, size_t col)
    {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("矩阵索引越界");
        }
        return data[row][col];
    }

    // 访问矩阵的元素（常量版本）
    const T& operator()(size_t row, size_t col) const
    {
        if (row >= rows || col >= cols) {
            throw std::out_of_range("矩阵索引越界");
        }
        return data[row][col];
    }

    // 获取矩阵的行数
    size_t getRows() const
    {
        return rows;
    }

    // 获取矩阵的列数
    size_t getCols() const
    {
        return cols;
    }

    // 打印矩阵
    void print() const
    {
        for (const auto& row : data) {
            for (const T& elem : row) {
                std::cout << elem << ' ';
            }
            std::cout << std::endl;
        }
    }

    // 重载*运算符作为矩阵乘法
    Matrix operator*(const Matrix& other) const
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
};

template <typename T>
class SquadMatrix : public Matrix<T> {
public:
    SquadMatrix(const std::vector<std::vector<T>>& vec) : Matrix<T>(vec)
    {
        if (this->getRows() != this->getCols()) {
            throw std::invalid_argument("不是方阵");
        }
    }

    SquadMatrix power(i64 exp) const
    {
        SquadMatrix result(identityMatrix(this->getRows()));
        SquadMatrix base(*this);

        while (exp > 0) {
            if (exp % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            exp /= 2;
        }

        return result;
    }

private:
    static SquadMatrix identityMatrix(size_t size)
    {
        std::vector<std::vector<T>> id(size, std::vector<T>(size, 0));
        for (size_t i = 0; i < size; ++i) {
            id[i][i] = 1;
        }
        return SquadMatrix(id);
    }
};

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    
    return 0;
}
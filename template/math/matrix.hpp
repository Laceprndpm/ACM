template <class T>
struct Matrix {
    vector<vector<T>> data;

    constexpr Matrix(const vector<vector<T>> &o)
    {
        this->data = o;
    }

    constexpr Matrix(vector<vector<T>> &&o)
    {
        this->data = std::move(o);
    }

    constexpr Matrix() {}

    friend constexpr Matrix operator*(const Matrix &lhs, const Matrix &rhs)
    {
        assert(lhs.data[0].size() == rhs.data.size());
        int               n = lhs.data.size(), p = lhs.data[0].size(), m = rhs.data[0].size();
        vector<vector<T>> res(n, vector<T>(m));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < p; k++) {
                for (int j = 0; j < m; j++) {
                    res[i][j] += lhs.data[i][k] * rhs.data[k][j];
                }
            }
        }
        return {res};
    }

    constexpr Matrix operator*=(const Matrix &o) &
    {
        *this = *this * o;
        return *this;
    }

    constexpr Matrix operator+=(const Matrix &o) &
    {
        assert(this->data.size() == o.data.size());
        assert(this->data[0].size() == o.data[0].size());
        for (int i = 0; i < this->data.size(); i++) {
            for (int j = 0; j < this->data[0].size(); j++) {
                this->data[i][j] += o.data[i][j];
            }
        }
        return *this;
    }
};

template <class T, int R, int C>
struct OMatrix {
    T data[R][C];

    constexpr OMatrix() = default;

    constexpr OMatrix(array<array<T, C>, R> const& init)
    {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                data[i][j] = init[i][j];
            }
        }
    }

    constexpr OMatrix operator*=(const OMatrix& o) &
    {
        *this = *this * o;
        return *this;
    }

    constexpr OMatrix operator+=(const OMatrix& o) &
    {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                this->data[i][j] += o.data[i][j];
            }
        }
        return *this;
    }
};

template <class T, int R, int K, int C>
constexpr OMatrix<T, R, C> operator*(const OMatrix<T, R, K>& lhs, const OMatrix<T, K, C>& rhs)
{
    OMatrix<T, R, C> res;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            T sum{};
            for (int k = 0; k < K; k++) {
                sum += lhs.data[i][k] * rhs.data[k][j];
            }
            res.data[i][j] = sum;
        }
    }
    return {res};
}

template <typename T, size_t R, size_t C>
OMatrix(array<array<T, C>, R> const& x) -> OMatrix<T, R, C>;

template <typename T, size_t RC>
constexpr OMatrix<T, RC, RC> identityMatrix = []() {
    OMatrix<T, RC, RC> id;
    for (int i = 0; i < RC; i++) {
        id.data[i][i] = T{1};
    }
    return id;
}();

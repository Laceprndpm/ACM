template <class T>
struct Matrix {
    vector<vector<T>> data;

    constexpr Matrix(const vector<vector<T>> &o)
    {
        this->data = o;
    }

    friend constexpr Matrix operator*(const Matrix &lhs, const Matrix &rhs)
    {
        assert(lhs.data[0].size() == rhs.data.size());
        int               n = lhs.data.size(), p = lhs.data[0].size(), m = rhs.data[0].size();
        vector<vector<T>> res(n, vector<T>(m));
        for (int i = 0; i < lhs.data.size(); i++) {
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
};
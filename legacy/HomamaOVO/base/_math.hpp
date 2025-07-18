
template <typename T>
T floor(T a, T b)
{
    return a / b - (a % b && (a ^ b) < 0);
}

template <typename T>
T ceil(T x, T y)
{
    return floor(x + y - 1, y);
}

template <typename T>
T bmod(T x, T y)
{
    return x - y * floor(x, y);
}

template <typename T>
pair<T, T> divmod(T x, T y)
{
    T q = floor(x, y);
    return {q, x - q * y};
}

template <typename T, typename U>
T SUM(const U &A)
{
    return std::accumulate(A.begin(), A.end(), T{});
}

template <class T>

tuple<T, T, T> exgcd(T a, T b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {1, 0, a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    T x = ly;
    T y = lx - ly * (a / b);
    return {x, y, r};
}
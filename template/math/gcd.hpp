i64 exgcd(i64 a, i64 b, i64 &x, i64 &y)
{
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

tuple<i64, i64, i64> exgcd(i64 a, i64 b)  // 找到a*x + b*y = r
{
    if (b == 0) {
        return {1, 0, a};
    }
    auto [lx, ly, r] = exgcd(b, a % b);
    // lx * b + ly * (a % b) = r
    // lx * b + ly * (a - (a / b) * b) = r
    // b * (lx - ly * (a / b)) + a * ly = r
    i64 x = ly;
    i64 y = lx - ly * (a / b);
    return {x, y, r};
}

template <typename T>
T stein_gcd(T a, T b)
{
    if (a == 0) return b;
    if (b == 0) return a;

    // a 和 b 都为偶数
    if ((a & 1) == 0 && (b & 1) == 0) return stein_gcd(a >> 1, b >> 1) << 1;

    // a 为偶数，b 为奇数
    if ((a & 1) == 0) return stein_gcd(a >> 1, b);

    // a 为奇数，b 为偶数
    if ((b & 1) == 0) return stein_gcd(a, b >> 1);

    // a 和 b 都为奇数，且 a >= b
    if (a >= b)
        return stein_gcd((a - b) >> 1, b);
    else
        return stein_gcd((b - a) >> 1, a);
}

// 大数可用，O(log(max{a, b}) ^ 2)
template <class T>
T stein_gcd(T u, T v)
{
    if (u == 0) return v;
    if (v == 0) return u;

    // 找出 u 和 v 共同的 2 的因子个数
    int shift = __builtin_ctzll(u | v);  // u | v 中最低的 1 的位置

    u >>= __builtin_ctzll(u);  // u 除尽所有2
    while (v != 0) {
        v >>= __builtin_ctzll(v);  // v 除尽所有2

        if (u > v) std::swap(u, v);  // 保证 u <= v
        v -= u;                      // v = v - u
    }

    return u << shift;  // 最终结果乘上2^shift
}

[[deprecated("实际更慢")]]
tuple<i64, i64, i64> exgcd(i64 a, i64 b)
{
    i64 x0 = 1, y0 = 0;
    i64 x1 = 0, y1 = 1;

    while (b != 0) {
        i64 q = a / b;
        i64 r = a % b;

        // 迭代替换
        i64 x2 = x0 - q * x1;
        i64 y2 = y0 - q * y1;

        // 更新 a, b, x0, y0, x1, y1
        a  = b;
        b  = r;
        x0 = x1;
        y0 = y1;
        x1 = x2;
        y1 = y2;
    }

    // 此时 a 是 gcd，x0, y0 是对应解
    return {x0, y0, a};
}
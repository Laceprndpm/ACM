namespace Poly_beta {
constexpr int CAPACITY = 1 << 21;

vector<Z> d(CAPACITY), b(CAPACITY), c(CAPACITY);

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change(vector<Z> &y)
{
    const int len = y.size();
    // 一开始 i 是 0...01，而 j 是 10...0，在二进制下相反对称。
    // 之后 i 逐渐加一，而 j 依然维持着和 i 相反对称，一直到 i = 1...11。
    for (int i = 1, j = len / 2, k; i < len - 1; i++) {
        // 交换互为小标反转的元素，i < j 保证交换一次
        if (i < j) swap(y[i], y[j]);
        // i 做正常的 + 1，j 做反转类型的 + 1，始终保持 i 和 j 是反转的。
        // 这里 k 代表了 0 出现的最高位。j 先减去高位的全为 1 的数字，直到遇到了
        // 0，之后再加上即可。
        k = len / 2;
        while (j >= k) {
            j = j - k;
            k = k / 2;
        }
        if (j < k) j += k;
    }
}

void ntt(vector<Z> &y, int on)
{
    const int len = y.size();
    assert((len == (len & -len)) && len);
    assert(len >= y.size());
    constexpr Z g = 3;

    // 位逆序置换
    change(y);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
        // wn：当前单位复根的间隔：w^1_h
        Z wn = power(g, (Z::mod() - 1) / h);
        if (on == -1) wn = wn.inv();
        // 合并，共 len / h 次。
        for (int j = 0; j < len; j += h) {
            // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
            // ...
            Z w(1);
            for (int k = j; k < j + h / 2; k++) {
                // 左侧部分和右侧是子问题的解
                Z u = y[k];
                Z t = w * y[k + h / 2];
                // 这就是把两部分分治的结果加起来
                y[k]         = u + t;
                y[k + h / 2] = u - t;
                // 后半个 「step」 中的ω一定和 「前半个」 中的成相反数
                // 「红圈」上的点转一整圈「转回来」，转半圈正好转成相反数
                // 一个数相反数的平方与这个数自身的平方相等
                w = w * wn;
            }
        }
    }
    // 如果是 IDFT，它的逆矩阵的每一个元素不只是原元素取倒数，还要除以长度 len。
    Z iv = Z(len).inv();
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i] = y[i] * iv;
        }
    }
}

void reserve_size(vector<Z> &vec, int n, int val = 0)
{
    if (n > vec.capacity()) {
        size_t cur_sz = 1ull << (n > 1 ? 64 - __builtin_clzll(n - 1) : 0);
        vec.reserve(cur_sz);
    }
    vec.resize(n, val);
}

/* 多项式乘积
 * a和b为多项式长度或者说，最高次+1
 * 即n = f.len + g.len - 1
 * 注意此处最高次项是长度-1
 * 请保证f和g的长度不小于n
 * 安全特化版本
 */
void convolution(vector<Z> &f, vector<Z> &g, bool unsafe = 0)
{
    int lens = 1;
    int n    = f.size() + g.size() - 1;
    while (lens < n) lens <<= 1;
    assert(unsafe || (f.capacity() >= lens && g.capacity() >= lens));
    // f.resize(lens, 0), g.resize(lens, 0);
    reserve_size(f, lens), reserve_size(g, lens);
    ntt(f, 1), ntt(g, 1);
    for (int i = 0; i < lens; i++) f[i] = f[i] * g[i];
    ntt(f, -1);
    f.resize(n);
    g.resize(0);
}

void mult(vector<Z> &f, vector<Z> const &g)
{
    int fsz = f.size(), gsz = g.size();
    int n = fsz + gsz - 1;

    for (int i = 0; i < n; i++) {
        for (int j = max(0, i - gsz); j < min(i, fsz); j++) {
            b[i] += f[j] * g[i - j];
        }
    }
    reserve_size(f, n);
    for (int i = 0; i < n; i++) {
        f[i] = b[i];
    }
}

/* 多项式求逆(inv)
 * n为f最高次
 * Q(2n) = 2Q(n) - P(n) \cdot Q^2(n)
 */
void polyinv(vector<Z> &f)
{
    const int n = f.size();
    for (i64 i = 0; i < n; i++) d[i] = 0;
    d[0] = f[0].inv();
    for (int i = 2; i <= n; i <<= 1) {
        b.resize(i << 1);
        c.resize(i << 1);
        d.resize(i);
        for (int j = 0; j < i; j++) b[j] = f[j];
        for (int j = i; j < 2 * i; j++) b[j] = 0;
        for (int j = 0; j < i / 2; j++) c[j] = d[j];
        for (int j = i / 2; j < 2 * i; j++) c[j] = 0;
        ntt(b, 1), ntt(c, 1);
        for (int j = 0; j < 2 * i; j++) b[j] = b[j] * c[j] * c[j];
        ntt(b, -1);
        for (int j = 0; j < i; j++) d[j] = 2ll * d[j] - b[j];
    }
    for (int i = 0; i < n; i++) f[i] = d[i];
}

void polyd(vector<Z> &f)
{
    const int n = f.size();
    for (int i = 0; i < n - 1; i++) {
        f[i] = f[i + 1] * (i + 1);
    }
    f.resize(n - 1);
}

void polyint(vector<Z> &f)
{
    const int n = f.size() + 1;
    f.resize(n);
    for (int i = n - 1; i > 0; i--) f[i] = f[i - 1] * Z(i).inv();
    f[0] = 0;
}

/* 多项式求ln
 * G(x) = ln(F(x)) => G'(x) = F'(x) / F(x) => G = int{F'/F}
 */
void polyln(vector<Z> &f)
{
    const int n = f.size();
    f.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) b[i] = f[i];
    polyd(b);
    polyinv(f);
    convolution(b, f);
    polyint(b);
    f.resize(n);
    for (int i = 0; i < n; i++) f[i] = b[i];
}

/* 多项式求exp
 * exp(x) = 1 + x + x^2/2! ... x^n / n!
 * F_{n} = exp(A) (mod x^n)
 * F_{2n} = F_n \cdot (1 - ln(F_n) + A) (mod x^{2n})
 */
void polyexp(vector<Z> &f, int n)
{
    c.resize(2);
    c[0] = 1;
    for (int i = 2; i <= n; i <<= 1) {
        b.resize(i);
        for (int j = 0; j < i; j++) b[j] = c[j];
        polyln(b);
        for (int j = 0; j < i; j++) b[j] = f[j] - b[j];
        b[0] = b[0] + 1;
        convolution(c, b);
        c.resize(2 * i);
        for (int j = i; j < 2 * i; j++) c[j] = 0;
    }
    // f.resize(n);
    reserve_size(f, n);
    for (int i = 0; i < n; i++) f[i] = c[i];
}

/* 多项式快速幂
 * G = F^k => lnG = k lnF => G = exp(k * lnF)
 */
void polyqpow(vector<Z> &f, int k)
{
    const int n = f.size();
    polyln(f);
    for (int i = 0; i < n; i++) f[i] = f[i] * k;
    polyexp(f, n);
}

Z lagrange(int x, vector<Z> &y_value, int n)
{
    if (x <= n) {
        return y_value[x];
    }
    Z wi = 1;
    for (int j = 1; j <= n; j++) {
        wi *= Z(x - j);
    }
    Z ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += y_value[i] * wi / (x - i) * comb.invfac(i - 1) * comb.invfac(n - i) * ((n - i) & 1 ? -1 : 1);
    }
    return ans;
}

};  // namespace Poly_beta
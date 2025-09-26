template <u32 P>
using MInt = ModInt<P>;

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
template <u32 P>
void change(vector<ModInt<P>> &y)
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

template <u32 P>
struct ntt_traits {
    static constexpr u32 g = 0;
};

template <>
struct ntt_traits<469762049> {
    static constexpr u32 g = 3;
};

template <>
struct ntt_traits<998244353> {
    static constexpr u32 g = 3;
};

template <>
struct ntt_traits<1004535809> {
    static constexpr u32 g = 3;
};

template <u32 P>
void ntt(vector<ModInt<P>> &y, int on)
{
    assert(ntt_traits<P>::g);
    constexpr MInt<P> g   = ntt_traits<P>::g;
    const int         len = y.size();
    assert((len == (len & -len)) && len);
    // 位逆序置换
    change(y);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
        // wn：当前单位复根的间隔：w^1_h
        assert(((P - 1) & (h - 1)) == 0);
        ModInt<P> wn = power(g, (P - 1) / h);
        if (on == -1) wn = wn.inv();
        // 合并，共 len / h 次。
        for (int j = 0; j < len; j += h) {
            // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
            // ...
            ModInt<P> w(1);
            for (int k = j; k < j + h / 2; k++) {
                // 左侧部分和右侧是子问题的解
                ModInt<P> u = y[k];
                ModInt<P> t = w * y[k + h / 2];
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
    ModInt<P> iv = ModInt<P>(len).inv();
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i] = y[i] * iv;
        }
    }
}

template <u32 P>
vector<MInt<P>> convolution(vector<MInt<P>> const &x, vector<MInt<P>> const &y)
{
    assert(x.size() == y.size());
    const u32 n = x.size();
    assert((n & -n) == n);
    constexpr i64      M[3] = {469762049, 998244353, 1004535809};
    vector<MInt<M[0]>> v11(n), v12(n);
    vector<MInt<M[1]>> v21(n), v22(n);
    vector<MInt<M[2]>> v31(n), v32(n);
    memcpy(v11.data(), x.data(), n * sizeof(int));
    memcpy(v21.data(), x.data(), n * sizeof(int));
    memcpy(v31.data(), x.data(), n * sizeof(int));
    memcpy(v12.data(), y.data(), n * sizeof(int));
    memcpy(v22.data(), y.data(), n * sizeof(int));
    memcpy(v32.data(), y.data(), n * sizeof(int));
    ntt(v11, 1), ntt(v12, 1);
    ntt(v21, 1), ntt(v22, 1);
    ntt(v31, 1), ntt(v32, 1);
    for (int i = 0; i < n; i++) {
        v11[i] *= v12[i];
        v21[i] *= v22[i];
        v31[i] *= v32[i];
    }
    ntt(v11, -1);
    ntt(v21, -1);
    ntt(v31, -1);
    constexpr i128  multi = i128(M[0]) * M[1] * M[2];
    constexpr i128  m0    = multi / M[0];
    constexpr i128  m1    = multi / M[1];
    constexpr i128  m2    = multi / M[2];
    vector<MInt<P>> res(n);
    for (int i = 0; i < n; i++) {
        constexpr i128 c0 = m0 * CInv<u32(m0 % M[0]), u32(M[0])>.val();
        constexpr i128 c1 = m1 * CInv<u32(m1 % M[1]), u32(M[1])>.val();
        constexpr i128 c2 = m2 * CInv<u32(m2 % M[2]), u32(M[2])>.val();
        res[i]            = u32((c0 * v11[i].val() + c1 * v21[i].val() + c2 * v31[i].val()) % multi % P);
    }
    return res;
}

template <u32 P>
void dft(vector<MInt<P>> &vec)
{
    ntt(vec, 1);
}

template <u32 P>
void idft(vector<MInt<P>> &vec)
{
    ntt(vec, -1);
}

template <int P = 998244353>
struct Poly : public vector<MInt<P>> {
    using Value = MInt<P>;

    Poly() : vector<Value>() {}

    explicit constexpr Poly(int n) : vector<Value>(n) {}

    explicit constexpr Poly(const vector<Value> &a) : vector<Value>(a) {}

    constexpr Poly(const initializer_list<Value> &a) : vector<Value>(a) {}

    template <class InputIt, class = _RequireInputIter<InputIt>>
    explicit constexpr Poly(InputIt first, InputIt last) : vector<Value>(first, last)
    {
    }

    template <class F>
    explicit constexpr Poly(int n, F f) : vector<Value>(n)
    {
        for (int i = 0; i < n; i++) {
            (*this)[i] = f(i);
        }
    }

    constexpr Poly shift(int k) const
    {
        if (k >= 0) {
            auto b = *this;
            b.insert(b.begin(), k, 0);
            return b;
        } else if (this->size() <= -k) {
            return Poly();
        } else {
            return Poly(this->begin() + (-k), this->end());
        }
    }

    constexpr Poly trunc(int k) const
    {
        Poly f = *this;
        f.resize(k);
        return f;
    }

    constexpr friend Poly operator+(const Poly &a, const Poly &b)
    {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] += b[i];
        }
        return res;
    }

    constexpr friend Poly operator-(const Poly &a, const Poly &b)
    {
        Poly res(max(a.size(), b.size()));
        for (int i = 0; i < a.size(); i++) {
            res[i] += a[i];
        }
        for (int i = 0; i < b.size(); i++) {
            res[i] -= b[i];
        }
        return res;
    }

    constexpr friend Poly operator-(const Poly &a)
    {
        vector<Value> res(a.size());
        for (int i = 0; i < int(res.size()); i++) {
            res[i] = -a[i];
        }
        return Poly(res);
    }

    constexpr friend Poly operator*(Poly a, Poly b)
    {
        if (a.size() == 0 || b.size() == 0) {
            return Poly();
        }
        if (a.size() < b.size()) {
            swap(a, b);
        }
        int n = 1, tot = a.size() + b.size() - 1;
        while (n < tot) {
            n *= 2;
        }
        if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
            Poly c(a.size() + b.size() - 1);
            for (int i = 0; i < a.size(); i++) {
                for (int j = 0; j < b.size(); j++) {
                    c[i + j] += a[i] * b[j];
                }
            }
            return c;
        }
        a.resize(n);
        b.resize(n);
        dft(a);
        dft(b);
        for (int i = 0; i < n; ++i) {
            a[i] *= b[i];
        }
        idft(a);
        a.resize(tot);
        return a;
    }

    // 三模数NTT
    // constexpr friend Poly operator*(Poly a, Poly b)
    // {
    //     if (a.size() == 0 || b.size() == 0) {
    //         return Poly();
    //     }
    //     if (a.size() < b.size()) {
    //         swap(a, b);
    //     }
    //     int n = 1, tot = a.size() + b.size() - 1;
    //     while (n < tot) {
    //         n *= 2;
    //     }
    //     // if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
    //     //     Poly c(a.size() + b.size() - 1);
    //     //     for (int i = 0; i < a.size(); i++) {
    //     //         for (int j = 0; j < b.size(); j++) {
    //     //             c[i + j] += a[i] * b[j];
    //     //         }
    //     //     }
    //     //     return c;
    //     // }
    //     a.resize(n);
    //     b.resize(n);
    //     // dft(a);
    //     // dft(b);
    //     // for (int i = 0; i < n; ++i) {
    //     //     a[i] *= b[i];
    //     // }
    //     // idft(a);
    //     auto res = convolution(a, b);
    //     res.resize(tot);
    //     return Poly{res};
    // }

    constexpr friend Poly operator*(Value a, Poly b)
    {
        for (int i = 0; i < int(b.size()); i++) {
            b[i] *= a;
        }
        return b;
    }

    constexpr friend Poly operator*(Poly a, Value b)
    {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] *= b;
        }
        return a;
    }

    constexpr friend Poly operator/(Poly a, Value b)
    {
        for (int i = 0; i < int(a.size()); i++) {
            a[i] /= b;
        }
        return a;
    }

    constexpr Poly &operator+=(Poly b) { return (*this) = (*this) + b; }

    constexpr Poly &operator-=(Poly b) { return (*this) = (*this) - b; }

    constexpr Poly &operator*=(Poly b) { return (*this) = (*this) * b; }

    constexpr Poly &operator*=(Value b) { return (*this) = (*this) * b; }

    constexpr Poly &operator/=(Value b) { return (*this) = (*this) / b; }

    constexpr Poly deriv() const
    {
        if (this->empty()) {
            return Poly();
        }
        Poly res(this->size() - 1);
        for (int i = 0; i < this->size() - 1; ++i) {
            res[i] = (i + 1) * (*this)[i + 1];
        }
        return res;
    }

    constexpr Poly integr() const
    {
        Poly res(this->size() + 1);
        for (int i = 0; i < this->size(); ++i) {
            res[i + 1] = (*this)[i] / (i + 1);
        }
        return res;
    }

    /* 多项式求逆(inv)
     * n为f最高次
     * Q(2n) = 2Q(n) - P(n) \cdot Q^2(n)
     */
    constexpr Poly inv(int m) const
    {
        Poly x{(*this)[0].inv()};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
        }
        return x.trunc(m);
    }

    /* 多项式求ln
     * G(x) = ln(F(x)) => G'(x) = F'(x) / F(x) => G = int{F'/F}
     */
    constexpr Poly log(int m) const { return (deriv() * inv(m)).integr().trunc(m); }

    /* 多项式求exp
     * exp(x) = 1 + x + x^2/2! ... x^n / n!
     * F_{n} = exp(A) (mod x^n)
     * F_{2n} = F_n \cdot (1 - ln(F_n) + A) (mod x^{2n})
     */
    constexpr Poly exp(int m) const
    {
        Poly x{1};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
        }
        return x.trunc(m);
    }

    /* 多项式快速幂
     * G = F^k => lnG = k lnF => G = exp(k * lnF)
     */
    constexpr Poly pow(int k, int m) const
    {
        int i = 0;
        while (i < this->size() && (*this)[i] == 0) {
            i++;
        }
        if (i == this->size() || 1LL * i * k >= m) {
            return Poly(m);
        }
        Value v = (*this)[i];
        auto  f = shift(-i) * v.inv();
        return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
    }

    constexpr Poly sqrt(int m) const
    {
        Poly x{1};
        int  k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
        }
        return x.trunc(m);
    }

    constexpr Poly mulT(Poly b) const
    {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }

    // 多项式求值
    constexpr vector<Value> eval(vector<Value> x) const
    {
        if (this->size() == 0) {
            return vector<Value>(x.size(), 0);
        }
        const int     n = max(x.size(), this->size());
        vector<Poly>  q(4 * n);
        vector<Value> ans(x.size());
        x.resize(n);
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < int(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int  m   = (l + r) / 2;
                Poly tmp = num.mulT(q[2 * p + 1]);
                tmp.resize(m - l);
                work(2 * p, l, m, tmp);
                tmp = num.mulT(q[2 * p]);
                tmp.resize(r - m);
                work(2 * p + 1, m, r, tmp);
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

using PolyZ = Poly<P>;

// floor(p / i) * i + p % i == p
// floor(p / i) * i + p % i == 0 (mod p)
// inv[i] == -inv[p % i] * floor(p / i)

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */

// asr
// using myfloat = double;

// myfloat simpson(myfloat l, myfloat r, auto &&f)
// {
//     myfloat mid = (l + r) / 2;
//     return (r - l) * (f(l) + myfloat(4) * f(mid) + f(r)) / 6;  // 辛普森公式
// }

// myfloat asr(myfloat l, myfloat r, myfloat eps, myfloat ans, int step, auto &&f)
// {
//     myfloat mid = (l + r) / 2;
//     myfloat fl = simpson(l, mid, f), fr = simpson(mid, r, f);
//     if (abs(fl + fr - ans) <= 15 * eps && step < 0) return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
//     return asr(l, mid, eps / 2, fl, step - 1, f) + asr(mid, r, eps / 2, fr, step - 1, f);   // 否则分割成两段递归求解
// }

// myfloat calc(myfloat l, myfloat r, myfloat eps, auto &&f) { return asr(l, r, eps, simpson(l, r, f), 2, f); }

// Z lagrange(int x, Z ptr[], int n)
// {
//     if (x <= n) {
//         return ptr[x];
//     }
//     Z wi = 1;
//     for (int j = 1; j <= n; j++) {
//         wi *= Z(x - j);
//     }
//     Z ans = 0;
//     for (int i = 1; i <= n; i++) {
//         ans += ptr[i] * wi / (x - i) * comb.invfac(i - 1) * comb.invfac(n - i) * ((n - i) & 1 ? -1 : 1);
//     }
//     return ans;
// }
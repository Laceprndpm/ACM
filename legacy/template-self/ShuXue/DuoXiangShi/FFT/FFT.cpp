#include <cmath>
#include <complex>

using Comp = std::complex<double>;  // STL complex

constexpr Comp I(0, 1);  // i
constexpr int  MAX_N = 1 << 20;

Comp tmp[MAX_N];

// rev=1,DFT; rev=-1,IDFT
void DFT(Comp* f, int n, int rev)
{
    if (n == 1) return;
    for (int i = 0; i < n; ++i)
        tmp[i] = f[i];
    // 偶数放左边，奇数放右边
    for (int i = 0; i < n; ++i) {
        if (i & 1)
            f[n / 2 + i / 2] = tmp[i];
        else
            f[i / 2] = tmp[i];
    }
    Comp *g = f, *h = f + n / 2;
    // 递归 DFT
    DFT(g, n / 2, rev), DFT(h, n / 2, rev);
    // cur 是当前单位复根，对于 k = 0 而言，它对应的单位复根 omega^0_n = 1。
    // step 是两个单位复根的差，即满足 omega^k_n = step*omega^{k-1}*n，
    // 定义等价于 exp(I*(2*M_PI/n*rev))
    Comp cur(1, 0), step(cos(2 * M_PI / n), sin(2 * M_PI * rev / n));
    for (int k = 0; k < n / 2; ++k) {  // F(omega^k_n) = G(omega^k*{n/2}) + omega^k*n\*H(omega^k*{n/2})
        tmp[k] = g[k] + cur * h[k];
        // F(omega^{k+n/2}*n) = G(omega^k*{n/2}) - omega^k_n*H(omega^k\_{n/2})
        tmp[k + n / 2] = g[k] - cur * h[k];
        cur *= step;
    }
    for (int i = 0; i < n; ++i)
        f[i] = tmp[i];
}
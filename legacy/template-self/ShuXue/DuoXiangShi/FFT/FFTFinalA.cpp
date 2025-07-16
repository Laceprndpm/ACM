struct Z {
    double x, y;

    Z(double _x = 0.0, double _y = 0.0)
    {
        x = _x;
        y = _y;
    }

    Z operator-(const Z &b) const
    {
        return Z(x - b.x, y - b.y);
    }

    Z operator+(const Z &b) const
    {
        return Z(x + b.x, y + b.y);
    }

    Z operator*(const Z &b) const
    {
        return Z(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

/*
 * 进行 FFT 和 IFFT 前的反置变换
 * 位置 i 和 i 的二进制反转后的位置互换
 * len 必须为 2 的幂
 */
void change(Z y[], int len)
{
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

void fft(Z y[], int len, int on)
{
    // 位逆序置换
    change(y, len);
    // 模拟合并过程，一开始，从长度为一合并到长度为二，一直合并到长度为 len。
    for (int h = 2; h <= len; h <<= 1) {
        // wn：当前单位复根的间隔：w^1_h
        Z wn(cos(2 * PI / h), sin(on * 2 * PI / h));
        // 合并，共 len / h 次。
        for (int j = 0; j < len; j += h) {
            // 计算当前单位复根，一开始是 1 = w^0_n，之后是以 wn 为间隔递增： w^1_n
            // ...
            Z w(1, 0);
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
    if (on == -1) {
        for (int i = 0; i < len; i++) {
            y[i].x /= len;
            y[i].y /= len;
        }
    }
}
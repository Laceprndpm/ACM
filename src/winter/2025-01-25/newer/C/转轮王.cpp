#include <cstdio>
#define int long long

int init() {
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c & 15);
    return x * f;
}

void print(int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x / 10)
        print(x / 10);
    putchar(x % 10 + '0');
}

const int N = (int)2e5 + 5;
int       f[N];

void Str(int k) {
    // 输出字典序第 k 个字母
    const char str1[] = {'s', 'p', 'd', 'f'};
    if (k <= 4) {
        putchar(str1[k - 1]);
        return;
    }
    const char str2[] = {'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'};
    if (k <= 13) {
        putchar(str2[k - 5]);
        return;
    }
    const char str3[] = {'q', 'r'};
    if (k <= 15) {
        putchar(str3[k - 14]);
        return;
    }
    const char str4[] = {'t', 'u', 'v', 'w', 'x', 'y', 'z'};
    if (k <= 22) {
        putchar(str4[k - 16]);
        return;
    }
    k -= 22;
    if (k <= 26 * 26) {
        putchar('a' + (k - 1) / 26);
        putchar('a' + (k - 1) % 26);
        return;
    }
    k -= 26 * 26;
    if (k <= 26 * 26 * 26) {
        putchar('a' + (k - 1) / 26 / 26);
        putchar('a' + (k - 1) / 26 % 26);
        putchar('a' + (k - 1) % 26);
        return;
    }
    k -= 26 * 26 * 26;
    if (k <= 26 * 26 * 26 * 26) {
        putchar('a' + (k - 1) / 26 / 26 / 26);
        putchar('a' + (k - 1) / 26 / 26 % 26);
        putchar('a' + (k - 1) / 26 % 26);
        putchar('a' + (k - 1) % 26);
        return;
    }
    k -= 26 * 26 * 26 * 26;
    putchar('a' + (k - 1) / 26 / 26 / 26 / 26);
    putchar('a' + (k - 1) / 26 / 26 / 26 % 26);
    putchar('a' + (k - 1) / 26 / 26 % 26);
    putchar('a' + (k - 1) / 26 % 26);
    putchar('a' + (k - 1) % 26);
    return;
}

signed main(signed argc, char** argv) {
// #ifndef ONLINE_JUDGE
//     freopen(argv[1], "r", stdin);
//     freopen(argv[2], "w", stdout);
// #endif
    for (int i = 1; i < N; ++i)
        f[i] = f[i - 1] + 2 * ((i + 1) / 2) * ((i + 1) / 2);
    int T = init();
    while (T--) {
        int a = init();
        int l = 1, r = N - 1;
        while (l < r) {
            int mid = l + r >> 1;
            if (f[mid] < a)
                l = mid + 1;
            else
                r = mid;
        }
        a -= f[l - 1];        // 减去前面若干斜行的和
        int k = (r + 1) / 2;  // 身处第 2k-1 / 2k 斜行
        int L = 1, R = k;
        while (L < R) {
            int mid = L + R >> 1;
            if ((4 * k - 2 * mid) * mid < a)
                L = mid + 1;
            else
                R = mid;
        }
        int i = L + R >> 1;  // 身处第 i 个容量
        if (l & 1) {
            // l = 2k - 1
            print(k + i - 1);
            Str(k - i + 1);
            print(a - (4 * k - 2 * (i - 1)) * (i - 1));
            putchar('\n');
        } else {
            // l = 2k
            print(k + i);
            Str(k - i + 1);
            print(a - (4 * k - 2 * (i - 1)) * (i - 1));
            putchar('\n');
        }
    }
}

/*
先找斜行的规律，设 $str=\tt spdf\cdots$，下标从 $1$ 开始。

第一斜行：$1s^2$；

第二斜行：$2s^2$；

第三斜行：$2p^6$，$3s^2$；

第四斜行：$3p^6$，$4s^2$；

第五斜行：$3d^{10}$，$4p^6$，$5s^2$；

第六斜行：$4d^{10}$，$5p^6$，$6s^2$；

第七斜行：$4f^{14}$，$5d^{10}$，$6p^6$，$7s^2$；

第八斜行：$5f^{14}$，$6d^{10}$，$7p^6$，$8s^2$；

可以有归纳结论：

第 $2k-1$ 斜行：$kstr_k^{2(2k-1)}$，$(k+1)str_{k-1}^{2(2k-3)}$，$\cdots$，$(2k-1)str_1^{2\times 1}$。

第 $2k$ 斜行：$(k+1)str_{k}^{2(2k-1)}$，$(k+2)str_{k-1}^{2(2k-3)}$，$\cdots$，$(2k)str_1^{2\times 1}$。

第 $2k-1/2k$ 斜行的数值和是：
$$
\begin{aligned}
&2\cdot(2k-1)+2\cdot(2k-3)+2\cdot(\cdots)+2\times 1\\
=&2\cdot\dfrac{1+(2k-1)}{2}\times\left[\dfrac{(2k-1)-1}{2}+1\right]\\
=&2k\times k=2k^2
\end{aligned}
$$
我们统计前 $1\sim i$ 个斜行的和，构造函数 $\mathbf f(i)$：
$$
\mathbf f(i)=2\cdot 1^2+2\cdot 1^2+2\cdot 2^2+2\cdot 2^2+\cdots
$$
然后利用二分算法确定第 $a$ 号元素在第几个斜行。

对于第 $2k-1/2k$ 个斜行，按顺序前 $i(1\le i\le k)$ 个容量和是：
$$
\begin{aligned}
&2\cdot(2k-1)+2\cdot(2k-3)+\cdots+2\cdot(2k+1-2i)\\
=&2\cdot\dfrac{(2k-1)+(2k+1-2i)}{2}\times i=(4k-2i)\cdot i
\end{aligned}
$$
*/

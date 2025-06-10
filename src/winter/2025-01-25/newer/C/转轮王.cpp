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
    // ����ֵ���� k ����ĸ
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
        a -= f[l - 1];        // ��ȥǰ������б�еĺ�
        int k = (r + 1) / 2;  // ���� 2k-1 / 2k б��
        int L = 1, R = k;
        while (L < R) {
            int mid = L + R >> 1;
            if ((4 * k - 2 * mid) * mid < a)
                L = mid + 1;
            else
                R = mid;
        }
        int i = L + R >> 1;  // ���� i ������
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
����б�еĹ��ɣ��� $str=\tt spdf\cdots$���±�� $1$ ��ʼ��

��һб�У�$1s^2$��

�ڶ�б�У�$2s^2$��

����б�У�$2p^6$��$3s^2$��

����б�У�$3p^6$��$4s^2$��

����б�У�$3d^{10}$��$4p^6$��$5s^2$��

����б�У�$4d^{10}$��$5p^6$��$6s^2$��

����б�У�$4f^{14}$��$5d^{10}$��$6p^6$��$7s^2$��

�ڰ�б�У�$5f^{14}$��$6d^{10}$��$7p^6$��$8s^2$��

�����й��ɽ��ۣ�

�� $2k-1$ б�У�$kstr_k^{2(2k-1)}$��$(k+1)str_{k-1}^{2(2k-3)}$��$\cdots$��$(2k-1)str_1^{2\times 1}$��

�� $2k$ б�У�$(k+1)str_{k}^{2(2k-1)}$��$(k+2)str_{k-1}^{2(2k-3)}$��$\cdots$��$(2k)str_1^{2\times 1}$��

�� $2k-1/2k$ б�е���ֵ���ǣ�
$$
\begin{aligned}
&2\cdot(2k-1)+2\cdot(2k-3)+2\cdot(\cdots)+2\times 1\\
=&2\cdot\dfrac{1+(2k-1)}{2}\times\left[\dfrac{(2k-1)-1}{2}+1\right]\\
=&2k\times k=2k^2
\end{aligned}
$$
����ͳ��ǰ $1\sim i$ ��б�еĺͣ����캯�� $\mathbf f(i)$��
$$
\mathbf f(i)=2\cdot 1^2+2\cdot 1^2+2\cdot 2^2+2\cdot 2^2+\cdots
$$
Ȼ�����ö����㷨ȷ���� $a$ ��Ԫ���ڵڼ���б�С�

���ڵ� $2k-1/2k$ ��б�У���˳��ǰ $i(1\le i\le k)$ ���������ǣ�
$$
\begin{aligned}
&2\cdot(2k-1)+2\cdot(2k-3)+\cdots+2\cdot(2k+1-2i)\\
=&2\cdot\dfrac{(2k-1)+(2k+1-2i)}{2}\times i=(4k-2i)\cdot i
\end{aligned}
$$
*/

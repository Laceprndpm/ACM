#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// 4 * (1^2 + 2 ^ 2 + ...)
LL MathWork1(LL n)
{
    return 4 * n * (n + 1) * (2 * n + 1) / 6;
}

LL MathWork15(LL n)
{
    return 2 * n * n;
}

LL BinSearch1(LL x)
{
    int l = -1;
    int r = 93592;
    while (l < r) {
        int mid = (r - l - 1) / 2 + 1 + l;
        if (MathWork1(mid) <= x) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    return l;
}

LL BinSearch2(LL x)
{
    int l = -1;
    int r = 93592;
    while (l < r) {
        int mid = (r - l - 1) / 2 + 1 + l;
        if (MathWork15(mid) <= x) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    return l;
}

void Str(int k)
{
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

void solve(void)
{
    LL n;
    cin >> n;
    int blocks = BinSearch1(n);
    n -= MathWork1(blocks);
    if (n == 0) {
        cout << 2 * blocks << 's' << 2 << '\n';
        return;
    }
    blocks++;  // 出于第ans1个循环的开始
    bool is2line = false;
    if (n >= MathWork15(blocks)) {
        n -= MathWork15(blocks);
        is2line = true;
    }
    if (n == 0) {
        cout << blocks * 2 - 1 << 's' << 2 << '\n';
        return;
    }
    //  0<=n<MathWork15(blocks)
    LL zuoshangjiao = blocks * 2 - 1;
    if (is2line) {
        zuoshangjiao++;
    }

    n = MathWork15(blocks) - n;  // 0<n<=MathWork15

    int points = BinSearch2(n);
    n          = MathWork15(points + 1) - n;

    zuoshangjiao -= points;
    cout << zuoshangjiao;
    Str(points + 1);
    cout << n << '\n';
}

signed main(int argc, char **argv)
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    // #ifndef ONLINE_JUDGE
    //     freopen(argv[1], "r", stdin);
    //     freopen(argv[2], "w", stdout);
    // #endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
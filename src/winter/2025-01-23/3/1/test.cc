#include <bits/stdc++.h>
#define int long long

int init() {
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

signed main(signed arc, char** argv) {
    int T = init();
    while (T--) {
        int n = init(), t = init();
        int lst = -t - 1, ans = 0;
        for (int i = 1; i <= n; ++i) {
            int l = init(), r = init() - 1;
            if (lst >= r)
                continue;
            int c1 = (r - lst + t - 1) / t;
            int c2 = 1 + (r - l) / t;
            if (c1 < c2)
                ans += c1, lst += t * c1;
            else
                ans += c2, lst = std::max(l, lst + 1) + t * c2 - 1;
        }
        print(ans), putchar('\n');
    }
}
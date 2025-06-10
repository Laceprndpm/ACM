#include <bits/stdc++.h>
#include <unistd.h>
#include <cstdio>
#define int     long long
#define in      inline
#define ri      register
#define _123hh2 0
using namespace std;

in int read()
{
    int  x = 0, f = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x  = (x << 3) + (x << 1) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

in void write(int x)
{
    if (x < 0) {
        x = -x;
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 2e5 + 5;
int       awa[maxn], n, k;

bool judge(int mid)
{
    map<int, bool> q;
    int            cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (awa[i] < mid) q[awa[i]] = 1;
        if (q.size() == mid) {
            // cout<<mid<<" "<<q.size()<<" "<<i<<endl;
            q.clear();
            cnt++;
        }
    }
    // n log n
    return cnt >= k;
}

signed main()
{
    int t = read();
    // 1e4
    while (t-- > 0) {
        n = read(), k = read();
        for (int i = 1; i <= n; i++)
            awa[i] = read();
        int l = 0, r = n + 1, ans = 0;
        // n log n
        while (l <= r) {
            int mid = (l + r) / 2;
            if (judge(mid))
                ans = mid, l = mid + 1;
            else
                r = mid - 1;
        }
        write(ans);
        putchar('\n');
    }
    return _123hh2;
}
#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

class SegmentTree {
private:
    int         n;
    vector<int> val;

    void update(int cur, int L, int R, int idx, int value)
    {
        val[cur] = max(value, val[cur]);
        if (L == R) {
            return;
        }
        int mid = (R - L) / 2 + L;
        if (idx <= mid) {
            update(cur * 2, L, mid, idx, value);
        } else {
            update(cur * 2 + 1, mid + 1, R, idx, value);
        }
    }

    int query(int cur, int L, int R, int l, int r)
    {
        if (r < L || R < l) {
            return INT32_MIN;
        }
        if (L == R) {
            return val[cur];
        }
        if (l <= L && R >= r) {
            return val[cur];
        }
        int mid = (R - L) / 2 + L;
        return max(query(cur * 2, L, mid, l, r), query(cur * 2 + 1, mid + 1, R, l, r));
    }

public:
    SegmentTree(int __n) : n(__n), val(4 * __n, INT32_MIN)
    {
    }

    void update(int idx, int value)
    {
        update(1, 1, n, idx, value);
    }

    int query(int l, int r)
    {
        return query(1, 1, n, l, r);
    }
};

int init()
{
    char c = getchar();
    int  x = 0, f = 1;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

void print(int x)
{
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}

signed main()
{
    int N, L, R;
    N = init();
    L = init();
    R = init();
    vector<int> input(N + 1);
    vector<int> dp(N + 1);
    for (int i = 0; i <= N; i++) {
        input[i] = init();
    }
    SegmentTree tre(N + 1);
    tre.update(N + 1, 0);
    for (int j = N; j >= 0; j--) {
        int start = min(j + L, N + 1), end = min(j + R, N + 1);
        if (start != N + 1)
            dp[j] = tre.query(start, end) + input[j];
        else {
            dp[j] = input[j];
        }
        tre.update(j, dp[j]);
    }
    print(dp[0]);
    return 0;
}
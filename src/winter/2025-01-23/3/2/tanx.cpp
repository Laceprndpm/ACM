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

using namespace std;
using LL = long long;

void solve() {
    LL n, k;
    cin >> n >> k;
    LL lst = 0;
    LL ans = 0;
    for (LL i = 1; i <= n; i++) {
        LL l, r;
        l = init();
        r = init();
        r--;
        if (r < lst)
            continue;
        LL start = max(l, lst);
        LL nums  = (r - start + 1 - 1) / k + 1;
        lst      = start + nums * k;
        ans += nums;
    }
    cout << ans << '\n';
}

signed main() {
    // ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    T = init();
    while (T--) {
        solve();
    }
    return 0;
}
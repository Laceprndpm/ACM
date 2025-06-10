#include <bits/stdc++.h>

using namespace std;

int       n, x, l, r, cnt = 2e9;
long long sum;

void solve()
{
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        // 假设i以前的牙齿全部整理好,且最小间距为cnt，l为r为上一个牙
        int a, b;
        cin >> a >> b;
        if (i == 1) l = a, r = b;
        sum += a + b;
        l   = min(l + x, a);
        r   = min(r + x, b);
        cnt = min(cnt, l + r);
    }
    cout << sum - 1LL * cnt * n << endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--)
        solve();
}
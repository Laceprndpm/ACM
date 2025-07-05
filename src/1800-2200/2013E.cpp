#include <bits/stdc++.h>

using namespace std;

int a[200200];
int n;

// 假设当前gcd为g
// 下一步我可以选择A / B，且gcd(g, A) < gcd(g, B)为最小
// 且假设B为最优路径
// 那么此时，假如顺序为 g B
// 我大可以插入A : g A B
// g + A + gcd(A, B) <= g + B
// A + gcd(A, B) <= B
//
void solve()
{
    cin >> n;
    int       g = 0, cur = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = __gcd(g, a[i]);
    }
    for (int i = 0; i < n; i++) {
        a[i] /= g;
    }
    for (int t = 0; t < n; t++) {
        int nc = 1e9;
        for (int i = 0; i < n; i++) {
            nc = min(nc, __gcd(cur, a[i]));
        }
        cur = nc;
        ans += cur;
        if (cur == 1) {
            ans += n - t - 1;
            break;
        }
    }
    cout << ans * g << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
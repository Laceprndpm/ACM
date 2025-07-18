#include <bits/stdc++.h>
using namespace std;
#define LL long long
LL n, m;

bool check(LL x)
{
    if ((1.0 * abs(x - m) / m) < 0.2) return 1;
    return 0;
}

void solve()
{
    cin >> n >> m;
    if (m * 4 <= n * 5) {
        for (int i = 1; i <= n; i++)
            cout << '0';
        cout << '\n';
        return;
    }
    if (m * 6 < n * 10 - 5) {
        cout << "-1\n";
        return;
    }
    bool ck = 0;
    for (int i = 0; i <= n; i++) {
        LL ans = i * (n - i) + n;
        if (ans >= m) ck = 1;
        if (check(ans)) {
            for (int j = 1; j <= i; j++)
                cout << 0;
            for (int j = 1; j <= n - i; j++)
                cout << 1;
            cout << endl;
            return;
        }
    }
    if (ck) {
        cout << -1 << endl;
        return;
    }
    for (int t = 3; t <= 6; t++) {
        int len = n / t;
        LL  ans = 1.0 * (t - 1) * n * n / 2 / t;
        if (check(ans)) {
            int cnt = 0;
            for (int i = 1; i <= t; i++) {
                for (int j = 1; j <= len; j++) {
                    cout << 0;
                    cnt++;
                    if (cnt == n) {
                        cout << endl;
                        return;
                    }
                }
                for (int j = 1; j <= i; j++) {
                    cout << 1;
                    cnt++;
                    if (cnt == n) {
                        cout << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << -1 << endl;
}

int main()
{
    int T;
    cin >> T;
    while (T-- > 0) {
        solve();
    }
    return 0;
}
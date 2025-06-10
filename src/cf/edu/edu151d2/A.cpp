#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using PII = pair<int, int>;

void solve()
{
    int n, k, x;
    cin >> n >> k >> x;
    if (x != 1) {
        cout << "YES\n";
        cout << n << '\n';
        for (int i = 1; i <= n; i++) {
            cout << 1 << ' ';
        }
        cout << '\n';
        return;
    } else {
        if (k == 1) {
            cout << "NO\n";
            return;
        } else if (k == 2) {
            if (n % 2 == 1) {
                cout << "NO\n";
                return;
            } else {
                cout << "YES" << '\n';
                cout << n / 2 << '\n';
                for (int i = 0; i < n / 2; i++) {
                    cout << 2 << ' ';
                }
                cout << '\n';
                return;
            }
        } else {
            if (n == 1) {
                cout << "NO\n";
                return;
            } else {
                if (n % 2 == 1) {
                    cout << "YES\n";
                    cout << 1 + (n - 3) / 2 << '\n';
                    cout << 3 << ' ';
                    for (int i = 0; i < (n - 3) / 2; i++) {
                        cout << 2 << ' ';
                    }
                    cout << '\n';
                    return;
                } else {
                    cout << "YES\n";
                    cout << n / 2 << '\n';
                    for (int i = 0; i < n / 2; i++) {
                        cout << 2 << ' ';
                    }
                    cout << '\n';
                    return;
                }
            }
        }
    }
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
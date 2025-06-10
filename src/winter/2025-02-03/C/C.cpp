#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve()
{
    int n, x;
    cin >> n >> x;
    int degree = 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        if (u == x || v == x) {
            degree++;
        }
    }
    if (degree == 1 || degree == 0) {
        cout << "Ayush" << '\n';
        return;
    }

    if (n % 2 == 1) {
        cout << "Ashish" << '\n';
    } else {
        cout << "Ayush" << '\n';
    }
    return;
}

signed main()
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
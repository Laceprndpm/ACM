#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int dVal[505];

void solve(void) {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> dVal[i];
    }
    for (int i = 1; i <= n - 1; i++) {
        cout << i << ' ' << i + 1 << '\n';
    }
    int lastplace = 2;
    for (int i = 1; i <= q; i++) {
        int place = n - dVal[i] + 1;
        cout << 1 << ' ' << lastplace << ' ' << place << '\n';
        lastplace = place;
    }
}

signed main() {
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
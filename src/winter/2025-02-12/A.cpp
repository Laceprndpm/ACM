#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int x, y;
        cin >> x >> y;
        if (y == x + 1) {
            cout << "Yes" << '\n';
            continue;
        }
        if (y < x && (x - y) % 9 == 8) {
            cout << "Yes" << '\n';
            continue;
        }
        cout << "No" << '\n';
        continue;
    }

    return 0;
}
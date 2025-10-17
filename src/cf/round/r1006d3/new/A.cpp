#include <iostream>

using namespace std;
// A
void solve()
{
    int n, k, p;
    cin >> n >> k >> p;
    int mnlen = (abs(k) + p - 1) / p;
    if (mnlen > n) {
        cout << "-1\n";
    } else {
        cout << mnlen << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

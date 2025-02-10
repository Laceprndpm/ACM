#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int input;
        cin >> input;
        cout << input / 10 + (input % 10 == 9 ? 1 : 0) << '\n';
    }
    return 0;
}
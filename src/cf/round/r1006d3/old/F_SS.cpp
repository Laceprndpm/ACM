#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    int T, n, k, i;
    for (cin >> T; T > 0; T--) {
        cin >> n >> k;
        n--;
        for (i = 0; i <= n; i++) {
            if ((n & i) == i)
                cout << k << ' ';
            else
                cout << "0 ";
        }
        cout << '\n';
    }
    return 0;
}

// 1 2 3 4 5 6 7 8
// 1 0 1 0 1 1 0 1
// (2, 1)
// 2
// 1
// 1 * 0
// 0   1
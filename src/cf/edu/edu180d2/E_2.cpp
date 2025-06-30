#include <bits/stdc++.h>

using namespace std;

const int M   = 5e5;
const int INF = 1e9;

int main()
{
    vector<int> dp(M + 1, INF);
    dp[0] = 0;
    dp[1] = 1;
    dp[3] = 2;
    // for (int m = 2; m <= M; ++m) {
    //     for (int i = 1; i * i <= m; ++i) {
    //         if (m % i != 0) continue;
    //         if (m / i > 2) dp[m] = min(dp[m], dp[i] + dp[m / i - 2]);
    //         if (i > 2) dp[m] = min(dp[m], dp[m / i] + dp[i - 2]);
    //     }
    // }
    for (int m = 2; m <= M; ++m) {
        for (int i = 1; i * i <= m; ++i) {
            if (m % i != 0) continue;
            if (i - 2 < 0 || m / i - 2 < 0) continue;
            dp[m] = min(dp[m], dp[i - 2] + dp[m / i - 2]);
            dp[m] = min(dp[m], dp[m / i - 2] + dp[i - 2]);
        }
    }
    // tree[t] = min{x, y, z | (x + 2)(y + 2)(z + 2)... = t}(tree[x] + tree[y] + tree[z]... + 1)
    // tree[t] = min{x, y | (x + 2)(y + 2)}(tree[x] + tree[y] + 1)
    // tree[t] = min{x, y | (x + 2)y}(tree[x] + tree[y])
    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        cout << (dp[m] == INF ? -1 : dp[m]) << '\n';
    }
}

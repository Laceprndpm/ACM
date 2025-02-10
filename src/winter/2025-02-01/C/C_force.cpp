// ----------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int m, k, n;

signed main(int argc, char** argv)
{

#ifndef ONLINE_JUDGE
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> m >> k;
    vector<int> input(m + 1);
    for (int i = 1; i <= m; i++) {
        cin >> input[i];
    }

    cin >> n;
    int lastans = 0;
    for (int i = 1; i <= n; i++) {
        int ai;
        cin >> ai;
        ai ^= lastans;
        int ans = 0;
        for (int j = 1; j <= m; j++) {
            if (input[j] <= ai + k && input[j] >= ai - k) {
                input[j] = INT32_MIN;
                ans++;
            }
        }
        lastans += ans;
        cout << lastans << '\n';
    }
    return 0;
}
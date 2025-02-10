#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> ai(n + 1);
    vector<LL>  prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> ai[i];
    }
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + ai[i];
    }
    LL totalDamage = 0;
    for (int i = 1; i <= q; i++) {
        LL ki;
        cin >> ki;
        totalDamage += ki;
        int numDown = upper_bound(prefix.begin() + 1, prefix.end(), totalDamage) - prefix.begin();
        int ans     = n - numDown + 1;
        if (ans == 0) {
            totalDamage = 0;
            ans         = n;
        }
        cout << ans << '\n';
    }
    return 0;
}
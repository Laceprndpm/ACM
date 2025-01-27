#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        vector<int> degree(n + 1, 0);
        for (int i = 1; i <= n - 1; i++)
        {
            int u, v;
            cin >> u >> v;
            degree[u]++;
            degree[v]++;
        }

        unordered_set<int> center;
        int count = 0;
        for (int iter : degree)
        {
            if (iter > 1)
            {
                center.insert(iter);
                count++;
                if (count > 2)
                    break;
            }
        }

        if (count == 0)
        {
            if (n == 2)
                cout << MOD - 2 << '\n';
            if (n == 1)
            {
                cout << 0 << '\n';
            }
        }
        else if (count == 1)
        {
            int ans = (n - 1) * (n - 1);
            ans -= n - 1;
            ans -= 2 * (n - 1);
            cout << ((ans % MOD) + MOD) % MOD << '\n';
        }
        else if (count == 2)
        {
            int ans = n * n;
            ans -= n;
            ans += 2 * (n - 1);
            ans += 2;
            cout << ((ans % MOD) + MOD) % MOD << '\n';
        }
        else
        {
            int ans = 0;
            ans += n * n;
            ans -= n;
            ans += 2 * (n - 1);
            cout << ((ans % MOD) + MOD) % MOD << '\n';
        }
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define int long long
// 可以观察到3+3+1 = 7
// 1+1+1+1+1 = 5
// 目的是从所有an中，找到a1+a2+a3...+ak+1 = n
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
        if (n == 1)
        {
            int temp;
            cin >> temp;
            cout << -1 << '\n';
            continue;
        }
        vector<list<int>> dp(n + 1);
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }

        dp[0].push_back(0);
        for (int i = 1; i <= n; i++) // items
        {
            for (int j = n - 1; j >= a[i]; j--) // weight
            {
                if (!dp[j - a[i]].empty() && dp[j].empty())
                {
                    for (auto iter : dp[j - a[i]]) // copy and push i
                    {
                        dp[j].push_back(iter);
                    }
                    dp[j].push_back(i);
                }
            }
        }
        if (dp[n - 1].empty()) // still empty
        {
            cout << -1 << '\n';
        }
        else
        {
            dp[n - 1].pop_front();            // 弹出0
            cout << dp[n - 1].size() << '\n'; // 这个list里有k个索引...
            unordered_set<int> has;
            for (int iter : dp[n - 1])
            {
                has.insert(iter);
            }
            vector<int> not_has;
            for (int i = 1; i <= n; i++)
            {
                if (has.find(i) == has.end())
                    not_has.emplace_back(i);
            }
            int preindex = 0;
            int cnt = 0;
            for (int iter : dp[n - 1])
            {
                cout << iter << ' ';
                int need = a[iter];
                if (preindex != 0)
                {
                    cout << preindex << ' ';
                    need--;
                }
                while (need--)
                {
                    cout << not_has[cnt] << ' ';
                    cnt++;
                }
                preindex = iter;
                cout << endl;
            }
        }
    }
    return 0;
}
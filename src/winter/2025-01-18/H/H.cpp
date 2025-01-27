#include <bits/stdc++.h>
using namespace std;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        unordered_map<int, unordered_set<int>> Graph;
        vector<int> in_degree(n + 5, 0);
        if (k <= 1 || n <= 2)
        {
            int temp;
            for (int i = 1; i <= k; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    cin >> temp;
                }
            }
            cout << "Yes" << '\n';
            continue;
        }
        for (int i = 1; i <= k; i++)
        {
            int temp;
            cin >> temp;
            int pre;
            cin >> pre;
            for (int j = 3; j <= n; j++)
            {
                int cnt;
                cin >> cnt;
                if (Graph[pre].find(cnt) == Graph[pre].end())
                {
                    Graph[pre].insert(cnt);
                    in_degree[cnt]++;
                }
                pre = cnt;
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            if (in_degree[i] == 0)
            {
                q.push(i);
            }
        }
        int count = 0;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            for (int neighbor : Graph[node])
            {
                in_degree[neighbor]--;
                if (in_degree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }
        if (count == n)
        {
            cout << "Yes" << '\n';
        }
        else
        {
            cout << "No" << '\n';
        }
    }
    return 0;
}
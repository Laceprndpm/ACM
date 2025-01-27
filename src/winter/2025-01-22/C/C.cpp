#include <bits/stdc++.h>
using namespace std;
using LL = long long;
void solve(void)
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int> degree(n + 1, 0);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    int max_degree = -1;
    int pre_max_sub = INT32_MAX;
    int pre_max_sub_num = INT32_MAX;
    int max_degree_index = 0;

    for (int i = 1; i <= n; i++)
    {
        if (degree[i] >= max_degree)
        {
            int max_sub = -1;
            int max_sub_num = 0;

            for (int sub : graph[i])
            {
                if (max_sub > degree[sub])
                {
                    max_sub = degree[sub];
                    max_sub_num = 1;
                }
                else if (max_sub == degree[sub])
                {
                    max_sub_num++;
                }
            }

            if (max_sub < pre_max_sub || (max_sub == pre_max_sub && pre_max_sub_num > max_sub_num))
            {
                max_degree_index = i;
                max_degree = degree[i];
                pre_max_sub = max_sub;
                pre_max_sub_num = max_sub_num;
                continue;
            }
        }
    }
    int ans = max_degree;
    degree[max_degree_index] = 0;
    for (int adj : graph[max_degree_index])
    {
        degree[adj]--;
    }
    max_degree = -1;
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] > max_degree)
        {
            max_degree = degree[i];
            continue;
        }
    }
    ans += max_degree - 1;
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

// a    b-1
// a-1  b
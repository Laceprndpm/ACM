#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int DFS(vector<vector<int>> &graph, vector<int> &degree, int root)
{
    int length = 1;
    int pre_node = root;
    int cnt_node = graph[root][0];
    while (degree[cnt_node] == 2)
    {
        length++;
        for (int adj : graph[cnt_node])
        {
            if (adj != pre_node)
            {
                pre_node = cnt_node;
                cnt_node = adj;
                break;
            }
        }
    }
    return length;
}

int DFS2(vector<vector<int>> &graph, vector<int> &degree, int root)
{
    int num_of_leaves = 0;
    for (int iter : graph[root])
    {
        int pre_node = root;
        int cnt_node = iter;
        while (degree[cnt_node] == 2)
        {
            for (int adj : graph[cnt_node])
            {
                if (adj != pre_node)
                {
                    pre_node = cnt_node;
                    cnt_node = adj;
                    break;
                }
            }
        }
        if (degree[cnt_node] == 1)
        {
            num_of_leaves++;
            continue;
        }
    }
    if (num_of_leaves == 2)
    {
        return 1;
    }
    else if (num_of_leaves == 3)
    {
        return 3;
    }
    return 0;
}
void solve(void)
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<int> degree(n + 1, 0);
    queue<int> que;
    LL ans = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
        degree[u]++;
        degree[v]++;
    }
    int num_of_leaves = 0;
    for (int i = 1; i <= n; i++)
    {
        if (degree[i] == 1)
        {
            ans += DFS(graph, degree, i) - 1;
            num_of_leaves++;
        }
    }

    if (num_of_leaves == 2)
    {
        ans++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (degree[i] == 3)
        {
            ans += DFS2(graph, degree, i);
        }
    }
    cout << n * (n - 1LL) / 2 - ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}

// 尝试hack数据(*/ω＼*)
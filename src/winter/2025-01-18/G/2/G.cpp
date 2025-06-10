#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 2e5 + 5;
char arr[2][N];
int n;

optional<pair<int, int>> step(int row, int col, map<pair<int, int>, bool> &visited) // 接收一个row和col，返回result
{
    if (col <= n)
    {
        if (arr[row][col] == '>')
        {
            col++;
        }
        else
        {
            col--;
        }

        if (col <= n && col >= 1)
        {
            return make_optional(pair<int, int>{row, col});
        }
        else if (col > n)
        {
            return make_optional(pair<int, int>{row, n});
        }
        else if (col < 1)
        {
            return make_optional(pair<int, int>{row, 1});
        }
    }
    return {};
}

bool BFS(void)
{
    map<pair<int, int>, bool> visited;
    queue<pair<int, int>> que;
    que.emplace(0, 1);
    while (!que.empty())
    {
        auto cnt = que.front();
        que.pop();
        if (visited[cnt] == false)
        {
            visited[cnt] = true;
            auto next1 = step(!cnt.first, cnt.second, visited);
            auto next2 = step(cnt.first, cnt.second + 1, visited);
            if (next1)
            {
                que.push(*next1);
            }
            if (next2)
            {
                que.push(*next2);
            }
        }
    }
    return visited[{1, n}] || visited[{1, n - 1}] || visited[{0, n}];
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[0][i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[1][i];
    }
    if (BFS())
    {
        cout << "YES" << '\n';
    }
    else
    {
        cout << "NO" << '\n';
    }
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
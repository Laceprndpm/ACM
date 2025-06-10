#ifdef V1
/**
 * @date 2024-12-3
 * 单调栈做法
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

int n, m;
const int N = 1005, M = 1005;
char input[N][M];
int prefix_sum[N][M];

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> input[i][j];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (input[i][j] == 'F')
                prefix_sum[i][j] = prefix_sum[i][j - 1] + 1;
        }
    }

    int ans = 0;

    for (int j = 1; j <= m; j++)
    {
        stack<int> s;
        vector<pair<int, int>> arr(n + 1);
        for (int i = 1; i <= n; i++)
        {
            while (!s.empty() && prefix_sum[s.top()][j] >= prefix_sum[i][j])
                s.pop();
            int l = s.empty() ? 1 : s.top() + 1;
            arr[i].first = l;
            s.push(i);
        }
        s.empty();
        for (int i = n; i >= 0; i--)
        {
            while (!s.empty() && prefix_sum[s.top()][j] >= prefix_sum[i][j])
                s.pop();
            int r = s.empty() ? n : s.top() - 1;
            arr[i].second = r;
            s.push(i);
        }
        for (int i = 1; i <= n; i++)
        {
            ans = max(prefix_sum[i][j] * (arr[i].second - arr[i].first + 1), ans);
        }
    }
    cout << 3 * ans << endl;
}
#endif
#define V2
#ifdef V2
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
struct block
{
    int l, r, h = 1;

} blocks[1005][1005];
char input[1005][1005];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> input[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (input[i][1] == 'F')
        {
            blocks[i][1].l = 1;
        }
        if (input[i][m] == 'F')
        {
            blocks[i][m].r = m;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j <= m; j++)
        {
            if (input[i][j] == 'F')
            {
                if (input[i][j - 1] == 'F')
                {
                    blocks[i][j].l = blocks[i][j - 1].l;
                }
                else
                {
                    blocks[i][j].l = j;
                }
            }
        }
        for (int j = m - 1; j >= 1; j--)
        {
            if (input[i][j] == 'F')
            {
                if (input[i][j + 1] == 'F')
                {
                    blocks[i][j].r = blocks[i][j + 1].r;
                }
                else
                {
                    blocks[i][j].r = j;
                }
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= m; j++)
    {
        if (input[1][j] == 'F')
        {
            int s = (blocks[1][j].r - blocks[1][j].l + 1) * blocks[1][j].h;
            ans = max(ans, s);
        }
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (input[i][j] == 'F')
            {
                if (input[i - 1][j] == 'F')
                {
                    blocks[i][j].l = max(blocks[i][j].l, blocks[i - 1][j].l);
                    blocks[i][j].r = min(blocks[i][j].r, blocks[i - 1][j].r);
                    blocks[i][j].h = blocks[i - 1][j].h + 1;
                }
                int s = (blocks[i][j].r - blocks[i][j].l + 1) * blocks[i][j].h;
                ans = max(ans, s);
            }
        }
    }
    cout << ans * 3 << '\n';
    return 0;
}
#endif
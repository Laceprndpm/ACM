#include <bits/stdc++.h>
using namespace std;

int n, m;
struct node
{
    int value = 0;
    bool male = false;
    bool female = false;
} arr[500005];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i].value;
    }
    while (m--)
    {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 1) // 标记1
        {
            for (int i = a; i <= b; i++)
            {
                arr[i].male = true;
            }
        }
        else if (c == 2) // 标记2
        {
            for (int i = a; i <= b; i++)
            {
                arr[i].female = true;
            }
        }
        else if (c == 3)
        {
            for (int i = a; i <= b; i++)
            {
                if (arr[i].male && arr[i].female)
                {
                    arr[i].value = 0;
                }
                arr[i].male = false;
                arr[i].female = false;
            }
        }
        else // 查询
        {
            int ans = 0;
            for (int i = a; i <= b; i++)
            {
                ans += arr[i].value;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
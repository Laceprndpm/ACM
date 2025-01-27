#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
int n_block;
int m;
struct node
{
    int value = 0;
    bool male = false;
    bool female = false;
} arr[600005];
struct block
{
    int sum = 0;
    bool male = false;
    bool female = false;
} block[100005];

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    n_block = sqrt(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i].value;
    }
    for (int i = 0; i <= n / n_block; i++)
    {
        for (int j = i * n_block; j < (i + 1) * n_block; j++)
        {
            block[i].sum += arr[j].value;
        }
    }
    while (m--)
    {
        int c, a, b;
        cin >> c >> a >> b;
        if (c == 1) // 标记1
        {
            int lp = a / n_block;
            int rp = b / n_block;
            for (int i = lp; i <= rp; i++)
            {
                if ((a <= i * n_block) && ((i + 1) * n_block - 1 <= b)) // 对于整块
                {
                    block[i].male = true;
                }
                else
                {
                    for (int j = max(a, i * n_block); j <= min(b, ((i + 1) * n_block - 1)); j++)
                    {
                        arr[j].male = true;
                    }
                }
            }
        }
        else if (c == 2) // 标记2
        {
            int lp = a / n_block;
            int rp = b / n_block;
            for (int i = lp; i <= rp; i++)
            {
                if ((a <= i * n_block) && ((i + 1) * n_block - 1 <= b)) // 对于整块
                {
                    block[i].female = true;
                }
                else
                {
                    for (int j = max(a, i * n_block); j <= min(b, ((i + 1) * n_block - 1)); j++)
                    {
                        arr[j].female = true;
                    }
                }
            }
        }
        else if (c == 3)
        {
            int lp = a / n_block;
            int rp = b / n_block;
            for (int i = lp; i <= rp; i++)
            {
                if ((a <= i * n_block) && ((i + 1) * n_block - 1 <= b)) // 对于整块
                {
                    if (block[i].sum == 0)
                    {
                        continue;
                    }
                    if (block[i].male && block[i].female) // 整块被打上了双标记
                    {
                        block[i].sum = 0;
                    }
                    else
                    {
                        if (block[i].male) // 下放标记
                        {
                            for (int j = i * n_block; j <= (i + 1) * n_block - 1; j++)
                            {
                                arr[j].male = true;
                            }
                            block[i].male = false;
                        }
                        if (block[i].female)
                        {
                            for (int j = i * n_block; j <= (i + 1) * n_block - 1; j++)
                            {
                                arr[j].female = true;
                            }
                            block[i].female = false;
                        }
                        for (int j = i * n_block; j <= ((i + 1) * n_block - 1); j++) // 当作散块处理
                        {
                            if (arr[j].male && arr[j].female)
                            {
                                block[i].sum -= arr[j].value;
                                arr[j].value = 0;
                            }
                            arr[j].male = false;
                            arr[j].female = false;
                        }
                    }
                }
                else
                {
                    if (block[i].male) // 下放标记
                    {
                        for (int j = i * n_block; j <= (i + 1) * n_block - 1; j++)
                        {
                            arr[j].male = true;
                        }
                        block[i].male = false;
                    }
                    if (block[i].female)
                    {
                        for (int j = i * n_block; j <= (i + 1) * n_block - 1; j++)
                        {
                            arr[j].female = true;
                        }
                        block[i].female = false;
                    }
                    for (int j = max(a, i * n_block); j <= min(b, ((i + 1) * n_block - 1)); j++) // 当作散块处理
                    {
                        if (block[i].sum == 0)
                            arr[j].value = 0;
                        else if (arr[j].male && arr[j].female)
                        {
                            block[i].sum -= arr[j].value;
                            arr[j].value = 0;
                        }
                        arr[j].male = false;
                        arr[j].female = false;
                    }
                }
            }
        }
        else // 查询
        {
            int lp = a / n_block;
            int rp = b / n_block;
            int ans = 0;
            for (int i = lp; i <= rp; i++)
            {
                if (a <= i * n_block && (i + 1) * n_block - 1 <= b) // 整块
                {
                    ans += block[i].sum;
                }
                else // 散块
                {
                    if (block[i].sum == 0) // 是否有懒惰标记
                    {
                        for (int j = i * n_block; j < (i + 1) * n_block; j++)
                        {
                            arr[j].value = 0;
                        }
                    }
                    for (int j = max(a, i * n_block); j <= min(b, ((i + 1) * n_block - 1)); j++)
                    {
                        ans += arr[j].value;
                    }
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
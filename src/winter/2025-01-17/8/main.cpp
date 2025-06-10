#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k;
int arr[60][60];
signed main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
        }
    }
    while (k--)
    {
        ll sum[60] = {0};
        for (int j = 1; j <= m; j++)
        {
            for (int i = 1; i <= n; i++)
            {
                sum[j] += arr[i][j];
            }
        }
        ll max_v = 0;
        ll min_v = INT64_MAX;
        list<int> max_mem;
        list<int> min_mem;
        for (int j = 1; j <= m; j++)
        {
            if (sum[j] > max_v)
            {
                max_v = sum[j];
                max_mem.clear();
                max_mem.push_back(j);
            }
            else if (sum[j] == max_v)
            {
                max_mem.push_back(j);
            }
            
            if (sum[j] < max_v)
            {
                min_v = sum[j];
                min_mem.clear();
                min_mem.push_back(j);
            }
            else if (sum[j] == max_v)
            {
                min_mem.push_back(j);
            }
        }
    }
}
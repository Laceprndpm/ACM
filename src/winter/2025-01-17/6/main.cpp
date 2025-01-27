#include <bits/stdc++.h>
using namespace std;
int n, m;
int a[60][60];
int sum[60];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }
    int max_sum = 0;
    int max_index = 0;
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            sum[j] += a[i][j];
        }
        if (sum[j] >= max_sum)
        {
            max_sum = sum[j];
            max_index = j;
        }
    }
    int best_num = 0;
    int best_score = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i][max_index] > best_score)
        {
            best_score = a[i][max_index];
            best_num = 1;
        }
        else if (a[i][max_index] == best_score)
        {
            best_num++;
        }
    }
    cout << best_score << ' ' << best_num;
    return 0;
}
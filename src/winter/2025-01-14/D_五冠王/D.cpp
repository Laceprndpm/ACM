#include <bits/stdc++.h>
using namespace std;

int n;
int arr[505][505][505];
int find(int x1, int y1, int z1, int x2, int y2, int z2)
{
    return arr[x2][y2][z2] - s[x1 - 1][y2][z2] - s[x2][y1 - 1][z2] - s[x2][y2][z1 - 1] + s[x1 - 1][y1 - 1][z2] + s[x1 - 1][y2][z1 - 1] + s[x2][y1 - 1][z1 - 1] - s[x1 - 1][y1 - 1][z1 - 1];
}
signed main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        arr[x][y][z]++;
    }
    // 转换成前缀和
    for (int i = 1; i <= 500; i++)
    {
        for (int j = 1; j <= 500; j++)
        {
            for (int k = 1; k <= 500; k++)
            {
                arr[i][j][k] += arr[i - 1][j][k] + arr[i][j - 1][k] + arr[i][j][k - 1] - arr[i - 1][j - 1][k] - arr[i - 1][j][k - 1] - arr[i][j - 1][k - 1] + arr[i - 1][j - 1][k - 1];
            }
        }
    }
    // 暴力枚举
    int ans = INT32_MAX;
    for (int i = 1; i <= 500; i++)
    {
        for (int j = 1; j <= 500; j++)
        {
            for (int k = 1; k <= 500; k++)
            {
                int xyz = arr[i][j][k] - arr[0][0][0];
                int xy_ = arr[i][j][500] - xyz;
                int x_z = arr[i][500][k] - xyz;
                int _yz = arr[500][j][k] - xyz;
                int x__ = arr[i][500][500] - xy_ - x_z - xyz;
                int _y_ = arr[500][j][500] - xy_ - _yz - xyz;
                int __z = arr[500][500][k] - x_z - _yz - xyz;
                int ___ = arr[500][500][500] - xyz - xy_ - x_z - x__ - _yz - _y_ - __z;
                ans = min(ans, max(max(max(max(max(max(max(xyz, xy_), x_z), x__), _yz), _y_), __z), ___));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
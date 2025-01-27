// #include <bits/stdc++.h>
// using namespace std;
// int n;
// int X[505];
// int Y[505];
// int Z[505];
// struct point
// {
//     int x;
//     int y;
//     int z;
// } points[505];

// signed main()
// {
//     cin >> n;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> X[i] >> Y[i] >> Z[i];
//         points[i] = {X[i], Y[i], Z[i]};
//     }
//     sort(&(X[1]), &(X[1]) + n);
//     sort(&(Y[1]), &(Y[1]) + n);
//     sort(&(Z[1]), &(Z[1]) + n);
//     int x = X[n / 2];
//     int y = Y[n / 2];
//     int z = Z[n / 2];
//     int xyz = 0;
//     int xy_ = 0;
//     int x_z = 0;
//     int x__ = 0;
//     int _yz = 0;
//     int _y_ = 0;
//     int __z = 0;
//     int ___ = 0;
//     for (int i = 1; i <= n; i++)
//         if (points[i].x > x && points[i].y > y && points[i].z > z)
//         {
//             xyz++;
//         }
//         else if (points[i].x > x && points[i].y > y && points[i].z <= z)
//         {
//             xy_++;
//         }
//         else if (points[i].x > x && points[i].y <= y && points[i].z > z)
//         {
//             x_z++;
//         }
//         else if (points[i].x > x && points[i].y <= y && points[i].z <= z)
//         {
//             x__++;
//         }
//         else if (points[i].x <= x && points[i].y > y && points[i].z > z)
//         {
//             _yz++;
//         }
//         else if (points[i].x <= x && points[i].y > y && points[i].z <= z)
//         {
//             _y_++;
//         }
//         else if (points[i].x <= x && points[i].y <= y && points[i].z > z)
//         {
//             __z++;
//         }
//         else if (points[i].x <= x && points[i].y <= y && points[i].z <= z)
//         {
//             ___++;
//         }
//     int num = max(max(max(max(max(max(max(xyz, xy_), x_z), x__), _yz), _y_), __z), ___);
//     cout << num << endl;
//     return 0;
// }
// int
// inline int lowbit(int x) { return x & -x; }
// void add(vector<int> &bit, int x, int v)
// {
//     for (int i = x; i < bit.size(); i += lowbit(i))
//     {
//         bit[i] += v;
//     }
// }

// int query(const vector<int> &bit, int x)
// {
//     int res = 0;
//     for (int i = x; i; i -= lowbit(i))
//     {
//         res += bit[i];
//     }
//     return res;
// }

/**
 * @author Myself
 * @date 2025-01-14
 * @AC
 */
#include <bits/stdc++.h>
using namespace std;

int n;
int arr[505][505][505];

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

/**
 * @author artalter
 * @date 2025-01-14
 * @AC
 */
#ifdef _
#include <bits/stdc++.h>
using namespace std;
int s[501][501][501];
int find(int x1, int y1, int z1, int x2, int y2, int z2)
{
    return s[x2][y2][z2] - s[x1 - 1][y2][z2] - s[x2][y1 - 1][z2] - s[x2][y2][z1 - 1] + s[x1 - 1][y1 - 1][z2] + s[x1 - 1][y2][z1 - 1] + s[x2][y1 - 1][z1 - 1] - s[x1 - 1][y1 - 1][z1 - 1];
}
inline int max(int a, int b)
{
    if (a <= b)
        return b;
    return a;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        s[x][y][z] = 1;
    }
    for (int i = 1; i <= 500; i++)
    {
        for (int j = 1; j <= 500; j++)
        {
            for (int k = 1; k <= 500; k++)
            {
                s[i][j][k] += s[i - 1][j][k] + s[i][j - 1][k] + s[i][j][k - 1] - s[i - 1][j - 1][k] - s[i - 1][j][k - 1] - s[i][j - 1][k - 1] + s[i - 1][j - 1][k - 1];
            }
        }
    }
    int ans = n;
    for (int i = 1; i <= 500; i++)
    {
        for (int j = 1; j <= 500; j++)
        {
            for (int k = 1; k <= 500; k++)
            {
                int t;
                t = max(s[i][j][k], s[i][j][500] - s[i][j][k]);
                t = max(t, max(s[i][500][k] - s[i][j][k], s[i][500][500] - s[i][500][k] - s[i][j][500] + s[i][j][k]));
                t = max(t, max(s[500][j][k] - s[i][j][k], s[500][j][500] - s[i][j][500] - s[500][j][k] + s[i][j][k]));
                t = max(t, max(s[500][500][k] - s[i][500][k] - s[500][j][k] + s[i][j][k], find(i, j, k, 500, 500, 500)));
                ans = min(ans, t);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
#endif
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
bool is_sharp(int x, int y)
{
    int edge = (n + 1) / 2;
    if (x > m - edge)
    {
        if (abs(y - edge) + x - m + edge <= edge)
            return true;
        else
            return false;
    }
    else
    {
        if (abs(y - edge) <= k / 2)
        {
            return true;
        }
    }
    return false;
}
signed main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (is_sharp(j, i))
            {
                cout << '#';
            }
            else
            {
                cout << '.';
            }
        }
        cout << '\n';
    }
    return 0;
}
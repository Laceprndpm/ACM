#include <bits/stdc++.h>
using namespace std;
int n;
signed main()
{
    cin >> n;
    list<int> ls1;
    list<int> ls2;
    for (int i = 1; i <= n; i++)
    {
        int temp;
        cin >> temp;
        if (temp <= 15)
        {
            ls1.push_back(temp);
        }
        else
        {
            ls2.push_back(temp);
        }
    }
    for (auto iter : ls1)
    {
        cout << iter << ' ';
    }
    for (auto iter : ls2)
    {
        cout << iter << ' ';
    }
    return 0;
}
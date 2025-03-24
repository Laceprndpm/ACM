#include <bits/stdc++.h>
using namespace std;
using LL = long long;
int num_score[605];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    int w;
    cin >> n >> w;
    for (int i = 1; i <= n; ++i)
    {
        int input;
        cin >> input;
        ++num_score[input];
        int sum = 0;
        for (int j = 600; j >= 0; j--)
        {
            sum += num_score[j];
            if (sum >= max(w * i / 100, 1))
            {
                cout << j << ' ';
                break;
            }
        }
    }
    return 0;
}
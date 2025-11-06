#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define pb push_back
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define int long long
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    cout << "cnt : ";
    for (int k = 1; k <= n; k++)
    {
        vector<int> brr = vector<int>(arr.begin(), arr.begin() + 1 + k);
        int cnt = 0;
        for (int ii = 1; ii <= k; ii++)
        {
            for (int jj = 1; jj <= k; jj++)
            {
                if (brr[ii] < brr[jj])
                {
                    cnt++;
                    swap(brr[ii], brr[jj]);
                }
            }
        }
        cout << cnt << ' ';
    }
    cout << '\n';
    for (int ii = 1; ii <= n; ii++)
    {
        for (int jj = 1; jj <= n; jj++)
        {
            if (arr[ii] < arr[jj])
            {
                swap(arr[ii], arr[jj]);
            }
        }
        cout << "i = " << ii << " : ";
        for (int jj = 1; jj <= n; jj++)
        {
            cout << arr[jj] << ' ';
        }
        cout << '\n';
    }
    // 1
    // 10
    // 10 9 8 7 6 5 4 3 2 1
    // 0 1 3 6 10 15 21 28 36 45
    // 1 2 3 4 5 6 7 8 9 10

    // 1
    // 10
    // 1 2 3 4 5 6 7 8 9 10
    // 0 2 4 6 8 10 12 14 16 18
    // 1 2 3 4 5 6 7 8 9 10
    cout << '\n';
    for (int i = 1; i <= n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
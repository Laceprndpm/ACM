#include <bits/stdc++.h>
using namespace std;
using LL = long long;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, c;
    cin >> n >> c;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }
    sort(arr.begin() + 1, arr.end());
    int l = 1, r = 1;
    LL ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (arr[l] < arr[i] - c && l <= n)
            l++;
        while (arr[r] <= arr[i] - c && r <= n)
            r++;
        ans += r - l;
    }
    cout << ans;
    return 0;
}
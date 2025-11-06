#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define pb push_back
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define int long long
signed main()
{
    int n, a, b;
    cin >> n >> a >> b;
    if (a + b - 2 <= n - 1)
    {
        string goleftup = string(n - 1, 'U') + string(n - 1, 'L');
        string ans = goleftup + string(a - 1, 'D') + string(b - 1, 'R');
        cout << ans;
    }
    else
    {
        string goleftup = string(n - 1, 'D') + string(n - 1, 'R');
        string ans = goleftup + string(n - a, 'U') + string(n - b, 'L');
        cout << ans;
    }
}
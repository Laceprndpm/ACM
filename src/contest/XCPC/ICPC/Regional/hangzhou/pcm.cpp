#include <bits/stdc++.h>

#include <vector>
using namespace std;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 10);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    map<int, int> mp;
    int           cnt = 0;
    int           ans = 0;
    if (n == 1) {
        cout << k << ' ' << k * (k + 1) / 2 << '\n';
        return;
    }
    for (int i = 1; i < n; i++) {
        int ma = max(a[i], a[i + 1]), mi = min(a[i], a[i + 1]);
        int res = ma - mi;
        for (int j = 1; j <= sqrt(res); j++) {
            if (res % j == 0) { 
                if (j >= mi + 1 && j-mi <= k) mp[j - mi]++;
                if (mp[j - mi] == n - 1) {
                    ans += j - mi;
                    cnt++;
                }
                int ano = res / j;
                if (ano >= mi + 1 && ano-mi <= k && ano - mi != j - mi) mp[ano - mi]++;
                if (ano - mi != j - mi && mp[ano - mi] == n - 1) {
                    ans += ano - mi;
                    cnt++;
                }
            }
        }
    }
    cout << cnt << ' ' << ans << '\n';
}

int main()
{
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
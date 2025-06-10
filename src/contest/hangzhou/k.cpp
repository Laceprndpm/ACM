#define REMOVE_ME
#include <bits/stdc++.h>

#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define int long long

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> pemu(n * m + 1);
    for (int i = 1; i <= n * m; i++) {
        cin >> pemu[i];
    }
    vector<int> row(n + 1);
    vector<int> nowrowmx(n * m + 1);
    for (int i = 1; i <= n * m; i++) {
        row[(pemu[i]-1) / m]++;
        nowrowmx[i] = max(nowrowmx[i - 1], row[(pemu[i]-1) / m]);
    }
    function<bool(int)> check = [&](int mid) -> int {
        if (m - nowrowmx[mid] <= k)
            return true;
        else
            return false;
    };
    int l = m;
    int r = n * m;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << '\n';
}

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
#include <algorithm>
#include <cmath>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
#define int long long

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    if (n == 1) {
        cout << k << ' ' << (k + 1) * k / 2 << '\n';
        return;
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    vector<int> tmp;
    n      = a.size();
    int ss = INF;
    for (int i = 1; i < n; i++) {
        ss = min(ss, a[i] - a[i - 1]);
    }
    int ans = 0;
    int cnt = 0;
    for (int i = 1; i <= min((int)sqrt(ss), k); i++) {
        if (ss % i == 0) {
            if (ss == i * i) {
                cnt++;
                ans += i - 1;
                continue;
            }
            cnt += 2;
            ans += i - 1;
            ans += ss / i - 1;
        }
    }
    cout << cnt - 1 << ' ' << ans << '\n';
}

signed main(signed argc, char** argv)
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
    while (t--)
        solve();
    return 0;
}
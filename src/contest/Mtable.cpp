#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(a.begin(), a.end());
    function<bool(int)> check = [&](int x) {
        for (int i = 0; i < n; i++) {
            if ((a[i] + x) % (a[0] + x) != 0) {
                return false;
            }
        }
        return true;
    };
    i64 cnt = 0;
    i64 ans = 0;
    for (int i = 1; i <= k; i++) {
        if (check(i)) {
            cnt++;
            ans += i;
        }
    }
    cout << cnt << ' ' << ans << '\n';
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
}
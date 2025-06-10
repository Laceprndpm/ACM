#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int helpF(int n, int m)
{
    int ans = 0;
    while (n > 1) {
        n = (n + 1) / 2;
        ans++;
    }
    while (m > 1) {
        m = (m + 1) / 2;
        ans++;
    }
    return ans;
}

void solve()
{
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int nn  = min(a, n - a + 1);
    int mm  = min(b, m - b + 1);
    int ans = min(helpF(nn, m), helpF(n, mm));
    ans++;
    cout << ans << '\n';
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
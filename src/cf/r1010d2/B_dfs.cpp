#include <cstdint>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

int dfsmax(int x, int n, int m)
{
    int ans = 0;
    if (n != 0) {
        ans = max(ans, dfsmax(x / 2, n - 1, m));
    }
    if (m != 0) {
        ans = max(ans, dfsmax((x + 1) / 2, n, m - 1));
    }
    if (n == 0 && m == 0) {
        return x;
    }
    return ans;
}

int dfsmin(int x, int n, int m)
{
    int ans = INT32_MAX;
    if (n != 0) {
        ans = min(ans, dfsmin(x / 2, n - 1, m));
    }
    if (m != 0) {
        ans = min(ans, dfsmin((x + 1) / 2, n, m - 1));
    }
    if (n == 0 && m == 0) {
        return x;
    }
    return ans;
}

void solve()
{
    int x, n, m;
    cin >> x >> n >> m;
    cout << dfsmin(x, n, m) << ' ' << dfsmax(x, n, m) << '\n';
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
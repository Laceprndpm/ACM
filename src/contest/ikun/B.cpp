#include <algorithm>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n, k;
    cin >> n >> k;
    vector<i64> remain(n + 1);
    i64         ans = 0;
    for (int i = 1; i <= n; i++) {
        i64 cur;
        cin >> cur;
        ans += cur / k;
        remain[i] = (k - cur % k ? k - cur % k : k);
    }
    i64 m;
    cin >> m;
    sort(remain.begin() + 1, remain.begin() + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (m < remain[i]) {
            break;
        }
        m -= remain[i];
        ans++;
    }
    if (m != 0) {
        ans += m / k;
    }
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
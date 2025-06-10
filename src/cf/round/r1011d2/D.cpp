#include <iostream>
#include <queue>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

/**
 *@Spell : greedy, regret greedy
 */

void solve()
{
    int n, k = 2;
    cin >> n;
    i64 ans = 0;
    i64 d   = 1;

    priority_queue<i64> pq;
    for (int i = 1; i <= 2 * n; i++) {
        int cur;
        cin >> cur;
        pq.push(cur);
        if (i % k == d) {
            ans += pq.top();
            pq.pop();
        }
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
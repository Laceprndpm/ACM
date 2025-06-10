#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> ab(n);
        for (int i = 0; i < n; i++) {
            cin >> ab[i].first;
        }
        for (int i = 0; i < n; i++) {
            cin >> ab[i].second;
        }
        sort(ab.begin(), ab.end());
        i64                 mx = ab[k - 1].first;
        priority_queue<int> que;
        int                 i;
        i64                 curSum = 0;
        for (i = 0; i < k; i++) {
            que.push(ab[i].second);
            curSum += ab[i].second;
        }
        i64 ans = mx * curSum;
        for (; i < n; i++) {
            mx = ab[i].first;
            if (ab[i].second < que.top()) {
                curSum -= que.top();
                que.pop();
                que.push(ab[i].second);
                curSum += ab[i].second;
            }
            ans = min(ans, curSum * mx);
        }
        cout << ans << '\n';
    }
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
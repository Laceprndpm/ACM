#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
i64           n, m, k;

bool check(i64 x)
{
    i64 num_long   = m / (x + 1);
    i64 max_perRow = x * (num_long) + m - num_long * (x + 1);
    return max_perRow * n >= k;
}

void solve()
{
    cin >> n >> m >> k;
    i64 left = 1, right = 1e9 + 1;
    while (left < right) {
        i64 mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    cout << right << endl;
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
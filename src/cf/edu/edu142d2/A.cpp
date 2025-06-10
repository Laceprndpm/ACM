#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 2);
    int         cnt = 0;

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (arr[i] == 1) {
            cnt++;
        }
    }
    cout << n - cnt + (cnt + 1) / 2 << '\n';
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
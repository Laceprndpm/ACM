#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    vector<int> last(1e6 + 50, -1);
    int         ans = INF;
    for (int i = 0; i < n; i++) {
        if (last[arr[i]] != -1) {
            ans = min(i - last[arr[i]] + 1, ans);
        }
        last[arr[i]] = i;
    }
    if (ans == INF) {
        cout << -1 << '\n';
        return 0;
    }
    cout << ans;
    return 0;
}
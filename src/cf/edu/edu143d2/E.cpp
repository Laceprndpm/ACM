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
    vector<i64> arr(n + 1);
    vector<i64> leftH(n + 1);
    vector<i64> rightH(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    // 注意只和基本生命值有关
    for (int i = 2; i <= n; i++) {
        leftH[i] = leftH[i - 1] + min(arr[i - 1], arr[i] - 1);
    }
    for (int i = n - 1; i >= 1; i--) {
        rightH[i] = rightH[i + 1] + min(arr[i + 1], arr[i] - 1);
    }
    i64 sumArr = 0;
    for (int i = 1; i <= n; i++) {
        sumArr += arr[i];
    }
    i64 maxH = 0;
    for (int i = 1; i <= n; i++) {
        maxH = max(maxH, rightH[i] + leftH[i]);
    }
    cout << sumArr - maxH << '\n';
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
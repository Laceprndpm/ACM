#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<i64> maxPrefix(n);
    vector<i64> minSufix(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    // priority_queue<i64, vector<i64>, greater<>> topmin;
    priority_queue<i64, vector<i64>, less<>> topmax;
    for (int i = 0; i < n; i++) {
        topmax.push(arr[i]);
        maxPrefix[i] = topmax.top();
    }
    // for (int i = n - 1; i >= 0; i--) {
    //     topmin.push(arr[i]);
    //     minSufix[i] = topmin.top();
    // }
    vector<i64> suffix(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + arr[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        cout << suffix[i] + (i ? (maxPrefix[i - 1] > arr[i] ? maxPrefix[i - 1] - arr[i] : 0) : 0) << ' ';
    }
    cout << '\n';
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
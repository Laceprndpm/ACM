#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& i : arr) {
        cin >> i;
    }
    int last = arr[0];
    int cnt  = 0;
    for (int i = 1; i < n - 1; i++) {
        int cur = arr[i];
        int nxt = arr[i + 1];
        if (cur >= last && cur <= nxt) {
            cnt++;
        } else if (cur <= last && cur >= nxt) {
            cnt++;
        } else {
            last = cur;
        }
    }
    if (n == cnt + 2 && arr[0] == arr[n - 1]) {
        cnt++;
    }
    cout << n - cnt << '\n';
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
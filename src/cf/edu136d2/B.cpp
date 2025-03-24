#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    int cur;
    cin >> cur;
    vector<int> arr(n + 1);
    vector<int> ans(n + 1);
    for (int i = 2; i <= n; i++) {
        cin >> arr[i];
    }
    ans[1] = cur;
    for (int i = 2; i <= n; i++) {
        int temp = arr[i];
        if (cur >= temp && temp != 0) {
            cout << -1 << '\n';
            return;
        }
        cur += temp;
        ans[i] = cur;
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
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
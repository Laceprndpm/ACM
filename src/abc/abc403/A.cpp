#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
    vector<int> arr(n + 1);
    i64         ans = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        if (i % 2) {
            ans += arr[i];
        }
    }
    cout << ans << '\n';
    return 0;
}
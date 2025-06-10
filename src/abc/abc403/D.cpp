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
    int n, d;
    cin >> n >> d;
    if (d == 0) {
        i64         ans = 0;
        vector<i64> cnt((i64)1e6 + 1);
        for (int i = 0; i < n; i++) {
            int cur;
            cin >> cur;
            cnt[cur]++;
            if (cnt[cur] > 1) {
                ans++;
            }
        }
        cout << ans << '\n';
        return 0;
    }
    vector<int> arr(n);
    vector<i64> cnt((i64)1e6 + 1);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    i64 ans = 0;
    for (int i = 0; i < d; i++) {
        i64 dp1 = 0, dp2 = 0;
        i64 ldp1 = 0, ldp2 = 0;
        for (int j = 0; j * d + i <= (i64)1e6; j++) {
            dp2  = min(ldp1 + cnt[i + j * d], ldp2 + cnt[i + j * d]);
            dp1  = ldp2;
            ldp1 = dp1, ldp2 = dp2;
        }
        ans += min(ldp1, ldp2);
    }
    cout << ans << '\n';
    return 0;
}
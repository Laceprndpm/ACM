#include <numeric>
#include <syncstream>
#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 ans = 0;
    i64 n, k;
    cin >> n >> k;
    vector<i64> arr(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    vector<i64> prefix(n + 2);
    prefix[0] = 0;
    vector<i64> suffix(n + 2);
    suffix[n + 1] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = gcd(prefix[i - 1], arr[i]);
    }
    for (int i = n; i >= 1; i--) {
        suffix[i] = gcd(suffix[i + 1], arr[i]);
    }
    ans = prefix[n];
    for (int i = 0; i <= n; i++) {
        if (prefix[i] != prefix[i + 1]) {
            i64 cur = prefix[i];
            for (int j = i + 1; j <= n; j++) {
                cur = gcd(cur, arr[j] + k);
                ans = max(ans, gcd(cur, suffix[j + 1]));
            }
        }
    }
    cout << ans << '\n';
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
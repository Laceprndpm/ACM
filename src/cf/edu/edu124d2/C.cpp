#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 n;
    cin >> n;
    vector<i64> arr(n);
    vector<i64> brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    i64 a1 = arr[0], a2 = arr[n - 1];
    i64 b1 = brr[0], b2 = brr[n - 1];
    i64 mina1 = INF, mina2 = INF;
    i64 minb1 = INF, minb2 = INF;
    for (int i = 0; i < n; i++) {
        mina1 = min(abs(brr[i] - a1), mina1);
        mina2 = min(abs(brr[i] - a2), mina2);
        minb1 = min(abs(arr[i] - b1), minb1);
        minb2 = min(abs(arr[i] - b2), minb2);
    }
    i64 ans = INT64_MAX;
    {
        i64 cur = abs(a1 - b1) + abs(a2 - b2);
        cur     = min(cur, abs(a1 - b2) + abs(a2 - b1));
        ans     = min(ans, cur);
    }
    {
        i64 cur = abs(a1 - b1) + mina2 + minb2;
        cur     = min(cur, abs(a1 - b2) + mina2 + minb1);
        cur     = min(cur, abs(a2 - b1) + mina1 + minb2);
        cur     = min(cur, abs(a2 - b2) + mina1 + minb1);
        ans     = min(ans, cur);
    }
    {
        i64 cur = mina1 + mina2 + minb1 + minb2;
        ans     = min(ans, cur);
    }
    cout << ans << '\n';
    return;
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
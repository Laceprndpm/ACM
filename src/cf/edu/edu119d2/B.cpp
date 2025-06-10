#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    i64 w, h;
    cin >> w >> h;
    i64 k;
    i64 l1, l2, r1, r2;
    cin >> k;
    cin >> l1;
    for (int i = 1; i < k; i++) {
        cin >> r1;
    }
    cin >> k;
    cin >> l2;
    for (int i = 1; i < k; i++) {
        cin >> r2;
    }
    i64 t1, t2, b1, b2;
    cin >> k;
    cin >> b1;
    for (int i = 1; i < k; i++) {
        cin >> t1;
    }
    cin >> k;
    cin >> b2;
    for (int i = 1; i < k; i++) {
        cin >> t2;
    }
    i64 ans = max(h * (max(r2 - l2, r1 - l1)), w * max(t1 - b1, t2 - b2));
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
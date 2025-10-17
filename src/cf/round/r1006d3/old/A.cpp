#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, k, q;
    cin >> n >> k >> q;
    k = abs(k);
    if (k == 0) {
        cout << 0 << '\n';
        return;
    }
    int operation = (k - 1) / q + 1;
    if (operation > n) {
        cout << -1 << '\n';
    } else {
        cout << operation << '\n';
    }
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
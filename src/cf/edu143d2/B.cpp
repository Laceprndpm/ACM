#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n, k;
    cin >> n >> k;
    int flag1 = 0, flag2 = 0;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        if (l == k) {
            flag1 = 1;
        }
        if (r == k) {
            flag2 = 1;
        }
    }
    if (flag1 && flag2) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
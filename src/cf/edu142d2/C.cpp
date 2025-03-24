#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    vector<int> num(n + 1);
    vector<int> place2val(n + 1);
    int         m1 = n / 2;
    int         m2 = m1 + 1;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++) {
        place2val[arr[i]] = i;
    }
    if (place2val[m1] > place2val[m2]) {
        cout << n / 2 << '\n';
        return;
    }
    while (m1 != 1 && place2val[m1 - 1] < place2val[m1]) {
        m1--;
    }
    while (m2 != n && place2val[m2 + 1] > place2val[m2]) {
        m2++;
    }
    int ans;
    if (n % 2) {
        int near = min((n / 2 + 1) - m1, m2 - (n / 2 + 1));
        ans      = n / 2 - near;
    } else {
        int near = min((n / 2) - m1 + 1, m2 - (n / 2 + 1) + 1);
        ans      = n / 2 - near;
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
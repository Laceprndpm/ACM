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
    vector<int> brr(n + 1);
    i64         sa = 0;
    i64         sb = 0;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        sa += arr[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> brr[i];
        sb += brr[i];
    }
    cout << sa + sb - *max_element(brr.begin() + 1, brr.end()) << '\n';
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
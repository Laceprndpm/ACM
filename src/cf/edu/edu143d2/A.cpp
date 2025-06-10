#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int n, m;
    cin >> n >> m;
    string A;
    string B;
    cin >> A >> B;
    reverse(B.begin(), B.end());
    A += B;
    int cnt = 0;
    for (int i = 0; i < n + m - 1; i++) {
        if (A[i] == A[i + 1]) {
            cnt++;
        }
    }
    if (cnt <= 1) {
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
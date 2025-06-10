#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

//              AB C
// AC B           | BC A         NO
// BC A | BC A    | AC B | AC B  NO
//
//

void solve()
{
    int n;
    cin >> n;
    if (n % 3 == 1) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
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
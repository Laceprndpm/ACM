#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int m;
    cin >> m;
    int                 ans = INF;
    vector<vector<int>> arr(2, vector<int>(m));
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }  // 假设：alice在j处下去了，bob似乎只能要么0， 要么m - 1
    vector<i64> prefix1(m + 1), prefix2(m + 1);
    for (int i = 0; i < m; i++) {
        prefix1[i + 1] += prefix1[i] + arr[0][i];
        prefix2[i + 1] += prefix2[i] + arr[1][i];
    }
    for (int i = 0; i < m; i++) {
        int cnt0 = prefix2[i];
        int cnt1 = prefix1[m] - prefix1[i + 1];
        ans      = min({ans, max({cnt0, cnt1})});
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
    //
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
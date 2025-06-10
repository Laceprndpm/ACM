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
    if (m > n) {
        cout << "NO\n";
    }
    // vector<pair<int, int>> arr(m);
    vector<int> row(n + 1);
    vector<int> col(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        // arr[i].first  = x;
        // arr[i].second = y;
        row[x]++;
        col[y]++;
    }
    int cntrow0 = 0;
    int cntrow2 = 0;
    int cntcol0 = 0;
    for (int i = 1; i <= n; i++) {
        if (row[i] > 2 || col[i] > 2) {
            cout << "NO\n";
            return;
        }
        if (row[i] == 2) {
            cntrow2++;
        }
        if (col[i] == 2) {
            cntrow2++;
        }
        if (row[i] == 0) {
            cntrow0++;
        }
        if (col[i] == 0) {
            cntcol0++;
        }
    }
    if (cntrow2 > 1) {
        cout << "NO\n";
        return;
    }
    if (cntrow0 > 0 || cntcol0 > 0) {
        cout << "YES\n";
        return;
    } else {
        cout << "NO\n";
        return;
    }

    //     for (int i = 0; i < m; i++) {
    //         if (row[arr[i].first] > 2) {
    //             for (int i = 1; i <= n; i++) {
    //                 if (row[i] == 0) {
    //                     row[arr[i].first]--;
    //                     goto END;
    //                 }
    //             }
    //         }
    //         if (col[arr[i].second] > 2) {
    //             for (int i = 1; i <= n; i++) {
    //                 if (col[i] == 0) {
    //                     col[arr[i].first]--;
    //                     goto END;
    //                 }
    //             }
    //         }
    //     }
    // END:
    //     for (int i = 1; i <= n; i++) {
    //         if (row[i] > 1 || col[i] > 1) {
    //             cout << "NO\n";
    //             return;
    //         }
    //     }
    //     cout << "YES\n";
    //     return;
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
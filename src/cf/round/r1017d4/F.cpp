#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

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
        int n, m;
        cin >> n >> m;
        int k;
        cin >> k;
        int                 a = gcd(n, k);
        int                 b = k / a;
        vector<vector<int>> ans(a, vector<int>(b));
        int                 cnt = 0;
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                ans[i][j] = ++cnt;
            }
        }
        if (a != 1 && b != 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[i % a][j % b] << ' ';
                }
                cout << '\n';
            }
        }
        if (a == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[0][(j + i) % b] << ' ';
                }
                cout << '\n';
            }
        }
        if (b == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << ans[(i + j) % a][0] << ' ';
                }
                cout << '\n';
            }
        }
        // 1 2 3
        // 1 2 3
        // 1 1 1
        // 2 2 2
        // 3 3 3
    }
    return 0;
}
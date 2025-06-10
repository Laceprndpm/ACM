#include <array>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    vector<vector<i64>> both(5, vector<i64>(5));
    int                 n;
    cin >> n;
    vector<array<bool, 5>> ok(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int cur;
            cin >> cur;
            ok[i][j] = cur;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            if (ok[i][j]) {
                for (int k = j; k < 5; k++) {
                    if (ok[i][k]) both[j][k]++;
                }
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (both[i][i] + both[j][j] - both[i][j] != n) {
                continue;
            }
            if (min(both[i][i], both[j][j]) >= n / 2) {
                cout << "Yes\n";
                return;
            }
        }
    }
    cout << "No\n";
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
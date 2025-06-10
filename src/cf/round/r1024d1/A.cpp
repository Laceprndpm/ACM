#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> bd(n, vector<int>(n));
    int                 cnt = n * n - 1;
    int                 l = 0, r = n - 1, top = 0, bt = n - 1;
    while (l <= r && bt >= top) {
        for (int i = l; i <= r; ++i) {
            bd[top][i] = cnt--;
        }
        top++;
        for (int i = top; i <= bt; ++i) {
            bd[i][r] = cnt--;
        }
        r--;
        if (top <= bt) {
            for (int i = r; i >= l; --i) {
                bd[bt][i] = cnt--;
            }
            bt--;
        }
        if (l <= r) {
            for (int i = bt; i >= top; --i) {
                bd[i][l] = cnt--;
            }
            l++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << bd[i][j] << ' ';
        }
        cout << '\n';
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
#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    int                 offset = m - 1;
    i64                 ans    = 0;
    vector<vector<int>> bd(n + 1, vector<int>(m + 1));
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= m; y++) {
            for (int c : {0, 1}) {
                int j = 1;
                while (true) {
                    int nx = x + (j + !c) / 2, ny = y + (j + c) / 2;
                    j++;
                    if (nx > n || ny > m) break;
                    ans++;
                }
            }
        }
    }
    ans += n * m;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        for (int c : {0, 1}) {
            int l = 1, r = 1;
            while (true) {
                int nx = x - (l + c) / 2, ny = y - (l + !c) / 2;
                if (nx <= 0 || ny <= 0 || bd[nx][ny] == 1) break;
                l++;
            }
            while (true) {
                int nx = x + (r + !c) / 2, ny = y + (r + c) / 2;
                if (nx > n || ny > m || bd[nx][ny] == 1) break;
                r++;
            }
            if (bd[x][y] == 1) {
                ans += l * r;
            } else {
                ans -= l * r;
            }
        }
        if (bd[x][y] == 1) {
            ans -= 1;
        } else {
            ans += 1;
        }
        bd[x][y] ^= 1;
        cout << ans << '\n';
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
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
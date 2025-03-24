#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int  n, m;
    bool fa = true;
    cin >> n >> m;
    vector<vector<bool>> board(n + 1, vector<bool>(m + 1));
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++) {
            if (s[j - 1] == '1') {
                board[i][j] = 1;
            }
        }
    }
    vector<bool> okCol(m + 1, true);
    vector<bool> okRow(n + 1, true);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!board[i][j]) {
                okCol[j] = false, okRow[i] = false;
            } else {
                if (!okCol[j] && !okRow[i]) {
                    fa = false;
                }
            }
        }
    }

    if (fa) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
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
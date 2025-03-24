#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

void solve()
{
    int row, col;
    cin >> row >> col;
    vector<vector<char>> board(row, vector<char>(col));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            char input;
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < row; i++) {
        bool cnt = 0;
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'U') {
                board[i][j]     = (cnt ? 'B' : 'W');
                board[i + 1][j] = (!cnt ? 'B' : 'W');
                cnt             = !cnt;
            }
        }
        if (cnt) {
            cout << "-1\n";
            return;
        }
    }
    for (int j = 0; j < col; j++) {
        bool cnt = 0;
        for (int i = 0; i < row; i++) {
            if (board[i][j] == 'L') {
                board[i][j]     = (cnt ? 'B' : 'W');
                board[i][j + 1] = (!cnt ? 'B' : 'W');
                cnt             = !cnt;
            }
        }
        if (cnt) {
            cout << "-1\n";
            return;
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << board[i][j];
        }
        cout << '\n';
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
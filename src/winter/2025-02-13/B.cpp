#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

char board[30][30];
bool num0[30][30];
char direct;
char direct_go[2];
int  n, m;

void go(int i, int j)
{
    if (!isalpha(board[i][j])) {
        return;
    }
    int nxt_i = i + direct_go[0], nxt_j = j + direct_go[1];
    if (nxt_i < 1 || nxt_i > n || nxt_j < 1 || nxt_j > m) {
        return;
    }

    if (board[nxt_i][nxt_j] == '.') {
        board[nxt_i][nxt_j] = board[i][j];
        board[i][j]         = '.';
        go(nxt_i, nxt_j);
    } else if (board[nxt_i][nxt_j] == '#') {
        return;
    }

    if (isdigit(board[nxt_i][nxt_j])) {
        if (board[nxt_i][nxt_j] == '1') {
            num0[nxt_i][nxt_j]  = true;
            board[nxt_i][nxt_j] = '.';
        } else {
            board[nxt_i][nxt_j]--;
        }
        board[i][j] = '.';
        return;
    }
}

void solve()
{
    if (direct == 'W') {
        direct_go[0] = 0;
        direct_go[1] = -1;
        for (int j = 1; j <= m; j++) {
            for (int i = 1; i <= n; i++) {
                go(i, j);
            }
        }
    }
    if (direct == 'E') {
        direct_go[0] = 0;
        direct_go[1] = 1;
        for (int j = m; j >= 1; j--) {
            for (int i = 1; i <= n; i++) {
                go(i, j);
            }
        }
    }
    if (direct == 'N') {
        direct_go[0] = -1;
        direct_go[1] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                go(i, j);
            }
        }
    }
    if (direct == 'S') {
        direct_go[0] = 1;
        direct_go[1] = 0;
        for (int i = n; i >= 1; i--) {
            for (int j = 1; j <= m; j++) {
                go(i, j);
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
        }
    }
    string command;
    cin >> command;
    for (char iter : command) {
        direct = iter;
        solve();
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (num0[i][j] && board[i][j] == '.') {
                cout << '0';
            } else {
                cout << board[i][j];
            }
        }
        cout << '\n';
    }
    return 0;
}
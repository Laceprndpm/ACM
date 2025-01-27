#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 5e4 + 5;
int           col[N];
int           row[N];

void solve(void) {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> board(n + 1, vector<char>(m + 1));
    memset(col, 0, sizeof(col));
    memset(row, 0, sizeof(row));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
            if (board[i][j] == '*') {
                row[i]++;
                col[j]++;
            }
        }
    }

    int       maxRow = 0;
    list<int> maxRow_idx;
    for (int i = 1; i <= n; i++) {
        if (row[i] > maxRow) {
            maxRow = row[i];
            maxRow_idx.clear();
            maxRow_idx.push_back(i);
        } else if (row[i] == maxRow) {
            maxRow_idx.push_back(i);
        }
    }

    int       maxCol = 0;
    list<int> maxCol_idx;
    for (int j = 1; j <= m; j++) {
        if (col[j] > maxCol) {
            maxCol = col[j];
            maxCol_idx.clear();
            maxCol_idx.push_back(j);
        } else if (col[j] == maxCol) {
            maxCol_idx.push_back(j);
        }
    }
    int ans = 0;
    for (int i : maxRow_idx) {
        for (int j : maxCol_idx) {
            if (board[i][j] == '.') {
                ans -= 1;
                goto LABEL;
            }
        }
    }
LABEL:
    ans += (n - maxRow) + (m - maxCol);
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
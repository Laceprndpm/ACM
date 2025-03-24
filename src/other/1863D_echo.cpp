#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define int long long
#define inf (int)1e18
#define pii pair<int, int>

void Echo2()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> mp(n + 1, vector<char>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
        }
    }
    vector<int> row(n + 1, 0);
    vector<int> col(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mp[i][j] == 'U') {
                if (row[i] >= 0 && row[i + 1] <= 0) {
                    mp[i][j]     = 'W';
                    mp[i + 1][j] = 'B';
                    row[i]--;
                    row[i + 1]++;
                } else {
                    mp[i][j]     = 'B';
                    mp[i + 1][j] = 'W';
                    row[i]++;
                    row[i + 1]--;
                }
            }
        }
    }
    for (int j = 1; j <= m; j++) {
        for (int i = 1; i <= n; i++) {
            if (mp[i][j] == 'L') {
                if (col[j] >= 0 && col[j + 1] <= 0) {
                    mp[i][j]     = 'W';
                    mp[i][j + 1] = 'B';
                    col[j]--;
                    col[j + 1]++;
                } else {
                    mp[i][j]     = 'B';
                    mp[i][j + 1] = 'W';
                    col[j]++;
                    col[j + 1]--;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (row[i] != 0) {
            // cout << i << ' ';
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= m; i++) {
        if (col[i] != 0) {
            cout << -1 << '\n';
            return;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << mp[i][j];
        }
        cout << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        Echo2();
    }
}
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }
    vector<vector<int>> prefixMax(n, vector<int>(m + 1));
    vector<vector<int>> prefixMin(n, vector<int>(m + 1, INF));
    vector<vector<int>> suffixMax(n, vector<int>(m + 1));
    vector<vector<int>> suffixMin(n, vector<int>(m + 1, INF));
    vector<int>         arr(n);
    iota(arr.begin(), arr.end(), 0);
    sort(arr.begin(), arr.end(), [&](int &a, int &b) {
        return board[a][0] > board[b][0];
    });
    sort(board.begin(), board.end(), [&](auto &a, auto &b) {
        return a[0] > b[0];
    });
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            prefixMax[i][j + 1] = max(prefixMax[i][j], board[i][j]);
            prefixMin[i][j + 1] = min(prefixMin[i][j], board[i][j]);
        }
        for (int j = m - 1; j >= 0; j--) {
            suffixMax[i][j] = max(suffixMax[i][j + 1], board[i][j]);
            suffixMin[i][j] = min(suffixMin[i][j + 1], board[i][j]);
        }
    }
    for (int j = 0; j < m - 1; j++) {
        vector<int> prefixLMin(n + 1, INF);
        vector<int> prefixRMax(n + 1);
        for (int i = 0; i < n; i++) {
            prefixLMin[i + 1] = min(prefixLMin[i], prefixMin[i][j + 1]);
            prefixRMax[i + 1] = max(prefixRMax[i], suffixMax[i][j + 1]);
        }
        vector<int> suffixLMax(n + 1);
        vector<int> suffixRMin(n + 1, INF);
        for (int i = n - 1; i >= 0; i--) {
            suffixLMax[i] = max(suffixLMax[i + 1], prefixMax[i][j + 1]);
            suffixRMin[i] = min(suffixRMin[i + 1], suffixMin[i][j + 1]);
        }
        vector<bool> ans(n, false);
        for (int i = 1; i < n; i++) {
            if (prefixLMin[i] > suffixLMax[i] && prefixRMax[i] < suffixRMin[i]) {
                cout << "Yes\n";
                for (int k = 0; k < i; k++) {
                    ans[arr[k]] = true;
                }
                for (int k = 0; k < n; k++) {
                    cout << (ans[k] ? 'R' : 'B');
                }
                cout << ' ' << j + 1 << '\n';
                return;
            }
        }
    }
    cout << "No\n";
    return;
}

signed main(int argc, char **argv)
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
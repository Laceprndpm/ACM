#include <bits/stdc++.h>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
using Graph       = vector<vector<int>>;
constexpr int INF = INT32_MAX;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n;
    cin >> n;
    vector<vector<bool>> grid(n, vector<bool>(n));
    for (int i = 0; i <= n / 2; i++) {
        for (int row = i; row < n - i; row++) {
            for (int col = i; col < n - i; col++) {
                grid[row][col] = (i % 2) == 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (grid[i][j] ? '#' : '.');
        }
        cout << '\n';
    }
    return 0;
}
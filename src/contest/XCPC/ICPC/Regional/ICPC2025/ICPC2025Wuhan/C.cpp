#include <iostream>
#include <vector>

using namespace std;

using vvi                  = vector<vector<int>>;
constexpr int sbstl[6][6]  = {{0, 0, 2, 2, 1, 1}, {1, 2, 0, 1, 2, 0}, {2, 1, 1, 0, 0, 2},
                              {2, 1, 1, 0, 0, 2}, {1, 2, 0, 1, 2, 0}, {0, 0, 2, 2, 1, 1}};
constexpr int sbsbsb[2][9] = {{0, 2, 1, 1, 2, 1, 0, 0, 2}, {2, 1, 1, 0, 2, 0, 0, 2, 1}};

void solve()
{
    int n, m;
    cin >> n >> m;
    bool tag = 0;
    if (n > m) {
        tag = 1;
        swap(n, m);
    }
    auto enter = [&tag](vector<vector<int>> board) -> void {
        cout << "Yes\n";
        if (!tag) {
            for (int i = 0; i < board.size(); i++) {
                for (int j = 0; j < board[0].size(); j++) {
                    cout << board[i][j];
                }
                cout << '\n';
            }
        } else {
            for (int j = 0; j < board[0].size(); j++) {
                for (int i = 0; i < board.size(); i++) {
                    cout << board[i][j];
                }
                cout << '\n';
            }
        }
        return;
    };
    if (n == 1) {
        if (m == 3) {
            enter(vvi{{0, 1, 2}});
        } else if (m == 6) {
            enter({{0, 0, 1, 1, 2, 2}});
        } else {
            cout << "No\n";
        }
        return;
    } else if (n == 2) {
        if (m == 3) {
            enter({{0, 1, 2}, {0, 1, 2}});
        } else if (m == 6) {
            enter({{0, 0, 1, 1, 2, 2}, {0, 0, 1, 1, 2, 2}});
        } else {
            cout << "No\n";
        }
    } else {
        vvi ans(n, vector<int>(m));
        if (n % 3 == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    ans[i][j] = sbstl[i % 6][j % 6];
                }
            }
        } else if (n % 3 == 1) {
            for (int i = 0; i < n - 1; i++) {
                for (int j = 0; j < m; j++) {
                    ans[i][j] = sbstl[i % 6][j % 6];
                }
            }
            for (int j = 0; j < m; j++) {
                ans[n - 1][j] = ans[n - 2][j];
            }
            if (m % 6 == 3) {
                int l      = m / 6 * 6 - 6;
                int choose = ans[n - 2][l] == 2;
                for (int j = 0; j < 9; j++) {
                    ans[n - 1][l + j] = sbsbsb[choose][j];
                }
            }
        } else {
            for (int i = 0; i < n - 2; i++) {
                for (int j = 0; j < m; j++) {
                    ans[i + 1][j] = sbstl[i % 6][j % 6];
                }
            }
            for (int j = 0; j < m; j++) {
                ans[n - 1][j] = ans[n - 2][j];
            }
            for (int j = 0; j < m; j++) {
                ans[0][j] = ans[1][j];
            }
            if (m % 6 == 3) {
                int l      = m / 6 * 6 - 6;
                int choose = ans[n - 2][l] == 2;
                for (int j = 0; j < 9; j++) {
                    ans[n - 1][l + j] = sbsbsb[choose][j];
                }
            }
            if (m % 6 == 3) {
                int l      = m / 6 * 6 - 6;
                int choose = ans[1][l] == 2;
                for (int j = 0; j < 9; j++) {
                    ans[0][l + j] = sbsbsb[choose][j];
                }
            }
        }
        enter(ans);
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

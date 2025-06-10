#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr i64 INF = 1e17;

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    vector<i64> costR(n), costC(n);
    for (int i = 0; i < n; i++) {
        cin >> costR[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> costC[i];
    }
    i64  ans = 0;
    i64  dpY = 0, dpN = 0;
    i64  curY, curN;
    bool ok = true;
    dpY     = costR[0];
    for (int i = 1; i < n; i++) {
        curY = INF, curN = INF;
        bool need1 = false, add1OK_preNo = true;
        for (int j = 0; j < n; j++) {
            if (board[i - 1][j] == board[i][j]) {
                need1 = true;
            }
            if (board[i - 1][j] == board[i][j] + 1) {
                add1OK_preNo = false;
            }
        }
        if (add1OK_preNo) {
            if (!need1) {
                curN = min(curN, dpN);
            }
            curY = min(curY, dpN + costR[i]);
        } else {
            if (!need1) {
                curN = min(curN, dpN);
            }
        }

        bool need2 = false, add1OK_preY = true;
        for (int j = 0; j < n; j++) {
            if (board[i - 1][j] + 1 == board[i][j]) {
                need2 = true;
            }
            if (board[i - 1][j] + 1 == board[i][j] + 1) {
                add1OK_preY = false;
            }
        }
        if (add1OK_preY) {
            if (!need2) {
                curN = min(curN, dpY);
            }
            curY = min(curY, dpY + costR[i]);
        } else {
            if (!need2) {
                curN = min(curN, dpY);
            }
        }

        dpY = curY, dpN = curN;
    }
    ans += min(dpN, dpY);
    dpN = 0;
    dpY = costC[0];
    for (int j = 1; j < n; j++) {
        curY = INF, curN = INF;
        bool need1 = false, add1OK_preNo = true;
        for (int i = 0; i < n; i++) {
            if (board[i][j - 1] == board[i][j]) {
                need1 = true;
            }
            if (board[i][j - 1] == board[i][j] + 1) {
                add1OK_preNo = false;
            }
        }
        if (add1OK_preNo) {
            if (!need1) {
                curN = min(curN, dpN);
            }
            curY = min(curY, dpN + costC[j]);
        } else {
            if (!need1) {
                curN = min(curN, dpN);
            }
        }

        bool need2 = false, add1OK_preY = true;
        for (int i = 0; i < n; i++) {
            if (board[i][j - 1] + 1 == board[i][j]) {
                need2 = true;
            }
            if (board[i][j - 1] + 1 == board[i][j] + 1) {
                add1OK_preY = false;
            }
        }
        if (add1OK_preY) {
            if (!need2) {
                curN = min(curN, dpY);
            }
            curY = min(curY, dpY + costC[j]);
        } else {
            if (!need2) {
                curN = min(curN, dpY);
            }
        }

        dpY = curY, dpN = curN;
    }
    ans += min(dpN, dpY);
    if (ans >= INF) {
        cout << -1 << '\n';
    } else {
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
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
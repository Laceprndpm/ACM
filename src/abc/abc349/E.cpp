#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64               = long long;
using PII               = pair<int, int>;
constexpr int       INF = 1e9;
vector<vector<i64>> WA(3, vector<i64>(3));
vector<vector<int>> bd(3, vector<int>(3));

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> WA[i][j];
        }
    }
    i64                 scA = 0, scB = 0;
    function<bool(int)> check = [&](int x) -> bool {
        int stan = -1;
        if (x % 2) {
            stan = 1;
        }
        int fianlWin = 0;
        for (int i = 0; i < 3; i++) {
            int canWin = 1;
            for (int j = 0; j < 3; j++) {
                canWin &= (stan == bd[i][j]);
            }
            fianlWin |= canWin;
        }
        for (int j = 0; j < 3; j++) {
            int canWin = 1;
            for (int i = 0; i < 3; i++) {
                canWin &= (stan == bd[i][j]);
            }
            fianlWin |= canWin;
        }
        {
            fianlWin |= ((bd[0][0] == stan) & (bd[1][1] == stan) & (bd[2][2] == stan));
        }
        {
            fianlWin |= ((bd[0][2] == stan) & (bd[1][1] == stan) & (bd[2][0] == stan));
        }
        return fianlWin;
    };
    function<bool(int d)> dfs = [&](int dep) -> bool {
        swap(scA, scB);
        if (check(dep - 1)) {
            swap(scA, scB);
            return false;
        }
        if (dep == 10) {
            if (scA > scB) {
                swap(scA, scB);
                return true;
            } else {
                swap(scA, scB);
                return false;
            }
        }
        bool canWin = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (bd[i][j] == 0) {
                    bd[i][j] = (dep % 2 == 0 ? -1 : 1);
                    scA += WA[i][j];
                    canWin |= !dfs(dep + 1);
                    bd[i][j] = 0;
                    scA -= WA[i][j];
                }
            }
        }
        swap(scA, scB);

        return canWin;
    };
    if (dfs(1)) {
        cout << "Takahashi\n";
    } else {
        cout << "Aoki\n";
    }
    return 0;
}
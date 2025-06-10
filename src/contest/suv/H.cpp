#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <utility>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

struct node {
    int r, c;

    friend istream& operator>>(istream& is, node& nd)
    {
        is >> nd.r >> nd.c;
        return is;
    }

    friend ostream& operator<<(ostream& os, node& nd)
    {
        os << nd.r << ' ' << nd.c;
        return os;
    }
};

template <class T>
ostream& operator<<(ostream& os, vector<T>& x)
{
    #ifdef DEBUG
    cout << '[';
    for (T i : x) {
        cout << i << ' ';
    }
    cout << ']';
    cout << '\n';
    #endif
    return os;
}

void solve()
{
    int n;
    cin >> n;
    vector<node> castles(n);
    vector<int>  originR2row;
    vector<int>  originC2col;
    for (int i = 0; i < n; i++) {
        cin >> castles[i];
        originR2row.push_back(castles[i].r);
        originR2row.push_back(castles[i].r + 1);
        originC2col.push_back(castles[i].c);
        originC2col.push_back(castles[i].c + 1);
    }
    int m;
    cin >> m;
    vector<node> obstacles(m);
    for (int i = 0; i < m; i++) {
        cin >> obstacles[i];
        originR2row.push_back(obstacles[i].r);
        originR2row.push_back(obstacles[i].r + 1);
        originC2col.push_back(obstacles[i].c);
        originC2col.push_back(obstacles[i].c + 1);
    }
    sort(originR2row.begin(), originR2row.end());
    sort(originC2col.begin(), originC2col.end());
    originR2row.erase(unique(originR2row.begin(), originR2row.end()), originR2row.end());
    originC2col.erase(unique(originC2col.begin(), originC2col.end()), originC2col.end());
    map<int, int> row2originR;
    map<int, int> col2originC;
    int           rowMax = originR2row.size();
    int           colMax = originC2col.size();
    for (int i = 0; i < rowMax; i++) {
        row2originR[originR2row[i]] = i;
    }
    for (int j = 0; j < colMax; j++) {
        col2originC[originC2col[j]] = j;
    }
    vector<vector<int>> sortBoard(rowMax, vector<int>(colMax));
    for (int i = 0; i < n; i++) {
        sortBoard[row2originR[castles[i].r]][col2originC[castles[i].c]] = 1;
    }
    for (int i = 0; i < m; i++) {
        sortBoard[row2originR[obstacles[i].r]][col2originC[obstacles[i].c]] = 2;
    }
    cout << sortBoard << '\n';
    for (int i = 0; i < rowMax; i++) {
        for (int j = 0; j < colMax; j++) {
            if ((i && sortBoard[i][j] == 1 && sortBoard[i - 1][j] == 1)
                || (j && sortBoard[i][j] == 1 && sortBoard[i][j - 1] == 1)) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    vector<vector<int>> isNeed(rowMax, vector<int>(colMax));
    // vector<vector<pair<int, int>>> RowNeed(rowMax);
    for (int i = 0; i < rowMax; i++) {
        bool flag = 0;
        int  last = -1;
        for (int j = 0; j < colMax; j++) {
            if (sortBoard[i][j] == 1) {
                if (flag) {
                    for (int k = last + 1; k <= j - 1; k++) {
                        isNeed[i][k]++;
                    }
                    // RowNeed[i].push_back({last + 1, j - 1});
                }
                last = j;
                flag = 1;
            }
            if (sortBoard[i][j] == 2) {
                flag = 0;
            }
        }
    }
    // vector<vector<pair<int, int>>> ColNeed(colMax);
    for (int j = 0; j < colMax; j++) {
        bool flag = 0;
        int  last = -1;
        for (int i = 0; i < rowMax; i++) {
            if (sortBoard[i][j] == 1) {
                if (flag) {
                    for (int k = last + 1; k <= i - 1; k++) {
                        isNeed[k][j]++;
                    }
                    // ColNeed[j].push_back({last + 1, i - 1});
                }
                last = i;
                flag = 1;
            }
            if (sortBoard[i][j] == 2) {
                flag = 0;
            }
        }
    }
    cout << isNeed << '\n';
    vector<node> ans;
    for (int i = 0; i < rowMax; i++) {
        for (int j = 0; j < colMax; j++) {
            if (isNeed[i][j] == 2) {
                isNeed[i][j] = 0;
                int il       = i - 1;
                int ir       = i + 1;
                while (il >= 0 && isNeed[il][j]) {
                    isNeed[il][j]--;
                    il--;
                }
                while (ir < rowMax && isNeed[ir][j]) {
                    isNeed[ir][j]--;
                    ir++;
                }
                int jl = j - 1;
                int jr = j + 1;
                while (jl >= 0 && isNeed[i][jl]) {
                    isNeed[i][jl]--;
                    jl--;
                }
                while (jr < colMax && isNeed[i][jr]) {
                    isNeed[i][jr]--;
                    jr++;
                }
                ans.push_back({originR2row[i], originC2col[j]});
            }
        }
    }
    for (int i = 0; i < rowMax; i++) {
        for (int j = 0; j < colMax; j++) {
            if (isNeed[i][j]) {
                isNeed[i][j] = 0;
                int il       = i - 1;
                int ir       = i + 1;
                while (il >= 0 && isNeed[il][j]) {
                    isNeed[il][j]--;
                    il--;
                }
                while (ir < rowMax && isNeed[ir][j]) {
                    isNeed[ir][j]--;
                    ir++;
                }
                int jl = j - 1;
                int jr = j + 1;
                while (jl >= 0 && isNeed[i][jl]) {
                    isNeed[i][jl]--;
                    jl--;
                }
                while (jr < colMax && isNeed[i][jr]) {
                    isNeed[i][jr]--;
                    jr++;
                }
                ans.push_back({originR2row[i], originC2col[j]});
            }
        }
    }
    cout << isNeed << '\n';
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << '\n';
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
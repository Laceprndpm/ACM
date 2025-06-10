#include <algorithm>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, pair<int, int>>> total(n * m);
    vector<vector<int>>               board(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            total[i * m + j].first  = board[i][j];
            total[i * m + j].second = {i, j};
        }
    }
    // vector<pair<int, int>> row(n, {INT32_MIN, 0});
    // vector<pair<int, int>> col(m, {INT32_MIN, 0});
    // for (int i = 0; i < n; i++) {
    //     row[i].second = i;
    //     for (int j = 0; j < m; j++) {
    //         row[i].first = max(row[i].first, board[i][j]);
    //     }
    // }
    // for (int j = 0; j < m; j++) {
    //     col[j].second = j;
    //     for (int i = 0; i < n; i++) {
    //         col[j].first = max(col[j].first, board[i][j]);
    //     }
    // }
    vector<bool> bombedRow(n, false);
    vector<bool> bombedCol(m, false);
    int          cnt = 0;
    sort(total.begin(), total.end(), greater<>());
    for (int i = 0; i < n * m; i++) {
        auto place = total[i].second;
        if (!bombedRow[place.first] && !bombedCol[place.second]) {
            bombedRow[place.first]  = true;
            bombedCol[place.second] = true;
            cnt++;
            if (cnt == k) break;
        }
    }
    // int          rowptr = 0, colptr = 0;
    // for (int i = 0; i < k; i++) {
    // }
    for (int i = 0; i < n; i++) {
        if (bombedRow[i]) continue;
        bool frst = true;
        for (int j = 0; j < m; j++) {
            if (!bombedCol[j]) {
                if (frst) {
                    cout << board[i][j];
                    frst = false;
                } else {
                    cout << ' ' << board[i][j];
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
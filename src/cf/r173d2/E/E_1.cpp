#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

bool canBeSorted(vector<vector<int>> &graph, vector<int> &degree, int num)
{
    queue<int> q;
    int        cnt = 0;
    for (int i = 0; i < num; i++) {
        if (degree[i] == 0) {
            q.emplace(i);
            cnt++;
        }
    }
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int iter : graph[cur]) {
            if (--degree[iter] == 0) {
                q.emplace(iter);
                cnt++;
            }
        }
    }
    return cnt == num;
}

void setcol(const int j, vector<bool> &row, vector<bool> &col, const vector<vector<int>> &matrixB, int n, int m, int d);

void setrow(const int i, vector<bool> &row, vector<bool> &col, const vector<vector<int>> &matrixB, int n, int m, int d)
{
    if (row[i]) {
        return;
    }
    row[i] = true;
    for (int j = 0; j < m; j++) {
        if (matrixB[i][j] >> d & 1) {
            setcol(j, row, col, matrixB, n, m, d);
        }
    }
}

void setcol(const int j, vector<bool> &row, vector<bool> &col, const vector<vector<int>> &matrixB, int n, int m, int d)
{
    if (col[j]) {
        return;
    }
    col[j] = true;
    for (int i = 0; i < n; i++) {
        if (!(matrixB[i][j] >> d & 1)) {
            setrow(i, row, col, matrixB, n, m, d);
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrixA(n, vector<int>(m));
    vector<vector<int>> matrixB(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrixA[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrixB[i][j];
        }
    }
    for (int d = 0; d < 30; d++) {
        vector<bool> row(n);
        vector<bool> col(m);
        bool         flg = true;
        for (int i = 0; i < n && flg; i++) {
            for (int j = 0; j < m && flg; j++) {
                if ((matrixB[i][j] >> d & 1) != (matrixA[i][j] >> d & 1)) {
                    flg = false;
                }
            }
        }
        if (flg) {
            continue;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int curA = matrixA[i][j] >> d & 1;
                int curB = matrixB[i][j] >> d & 1;
                if (!curA && curB) {  // A没，B有
                    setcol(j, row, col, matrixB, n, m, d);
                }
                if (curA && !curB) {
                    setrow(i, row, col, matrixB, n, m, d);
                }
            }
        }
        vector<vector<int>> graph(n + m);
        vector<int>         degree(n + m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (row[i] && col[j]) {
                    int curB = matrixB[i][j] >> d & 1;
                    if (curB) {  // col后
                        graph[i].emplace_back(j + n);
                        degree[j + n]++;
                    } else {  // row后
                        graph[j + n].emplace_back(i);
                        degree[i]++;
                    }
                }
            }
        }
        if (!canBeSorted(graph, degree, n + m)) {
            cout << "No" << '\n';
            return;
        }
    }
    cout << "Yes" << '\n';
}

signed main(int argc, char **argv)
{
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
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
#include <bits/stdc++.h>
using namespace std;
using LL  = long long;
using PII = pair<int, int>;

int matrixA[1005][1005];
int matrixB[1005][1005];
int n, m;

void operationAND(int row, int x)
{
    for (int j = 1; j <= m; j++) {
        matrixA[row][j] &= x;
    }
}

void operationOR(int col, int x)
{
    for (int i = 1; i <= n; i++) {
        matrixA[i][col] |= x;
    }
}

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrixA[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> matrixB[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int andX = matrixA[i][j] & (~matrixB[i][j]);  // 在A上有，但B没有
            operationAND(i, (~andX) & INT32_MAX);
            int orX = ~matrixA[i][j] & (matrixB[i][j]);  // 在A上没有，但B有
            operationOR(j, orX & INT32_MAX);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int andX = matrixA[i][j] & (~matrixB[i][j]);  // 在A上有，但B没有
            operationAND(i, (~andX) & INT32_MAX);
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (matrixA[i][j] != matrixB[i][j]) {
                cout << "No" << '\n';
                return;
            }
        }
    }
    cout << "Yes" << '\n';
    return;
}

signed main()
{
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
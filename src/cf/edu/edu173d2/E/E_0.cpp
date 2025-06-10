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
    int maxtry = 10;
label:
    if (maxtry)
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int andX = matrixA[i][j] & (~matrixB[i][j]);  // 在A上有，但B没有
                operationAND(i, ~andX);
                int orX = ~matrixA[i][j] & (matrixB[i][j]);  // 在A上没有，但B有
                operationOR(j, orX);
                if (andX != 0 || orX != 0) {
                    goto label;
                    maxtry--;
                }
            }
        }
    else {
        cout << "NO" << '\n';
    }
    cout << "YES" << '\n';
    return;
}

int main(int argc, char** argv)
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
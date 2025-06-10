#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 1e3 + 5;

int diff_2d[N][N];
int input[N][N];
int presum_diff_2d[N][N];

void update(int x1, int y1, int x2, int y2) {
    diff_2d[y1][x1]++;
    diff_2d[y1][x2 + 1]--;
    diff_2d[y2 + 1][x1]--;
    diff_2d[y2 + 1][x2 + 1]++;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int x1, y1, x2, y2;
        cin >> y1 >> x1 >> y2 >> x2;
        update(x1, y1, x2, y2);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            presum_diff_2d[i][j] =
                presum_diff_2d[i - 1][j] + presum_diff_2d[i][j - 1] - presum_diff_2d[i - 1][j - 1] + diff_2d[i][j];
            cout << presum_diff_2d[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

constexpr int N = 125;

int input[N][N];
int presum[N][N];

int query(int x2, int y2, int x1, int y1) {
    int ans = 0;
    ans += presum[y1][x1];
    ans -= presum[y2 - 1][x1];
    ans -= presum[y1][x2 - 1];
    ans += presum[y2 - 1][x2 - 1];
    return ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> presum[i][j];
            presum[i][j] += presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1];
        }
    }
    int ans = INT32_MIN;
    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= n; y1++) {
            for (int x2 = 1; x2 <= x1; x2++) {
                for (int y2 = 1; y2 <= y1; y2++) {
                    ans = max(ans, query(x2, y2, x1, y1));
                }
            }
        }
    }
    cout << ans;
    return 0;
}
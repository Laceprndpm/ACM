#include <vector>
#define REMOVE_ME
#include <iostream>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;
bool          vis[5][5];

int mydfs(int cur, int num)
{
    i64 ans = 0;
    int row = cur / 4;
    int col = cur % 4;
    if (num == 16) {
        return 1;
    }
    if (row - 1 >= 0 && !vis[row - 1][col]) {
        vis[row - 1][col] = true;
        ans += mydfs((row - 1) * 4 + col, num + 1);
        vis[row - 1][col] = false;
    }
    if (row + 1 <= 3 && !vis[row + 1][col]) {
        vis[row + 1][col] = true;
        ans += mydfs((row + 1) * 4 + col, num + 1);
        vis[row + 1][col] = false;
    }
    if (col - 1 >= 0 && !vis[row][col - 1]) {
        vis[row][col - 1] = true;
        ans += mydfs(row * 4 + col - 1, num + 1);
        vis[row][col - 1] = false;
    }
    if (col + 1 <= 3 && !vis[row][col + 1]) {
        vis[row][col + 1] = true;
        ans += mydfs(row * 4 + col + 1, num + 1);
        vis[row][col + 1] = false;
    }
    return ans;
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
    i64 ans = 0;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            vis[r][c] = true;
            ans += mydfs(r * 4 + c, 1);
            vis[r][c] = false;
        }
    }
    cout << ans;
    return 0;
}
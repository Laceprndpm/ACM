#include <format>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
using i64         = long long;
using PII         = pair<int, int>;
constexpr int INF = 1e9;

signed main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int r, c;
    cin >> r >> c;
    vector<string> bd(r + 1);
    for (int i = 1; i <= r; i++) {
        cin >> bd[i];
        bd[i] = '0' + bd[i];
    }
    int dx[]  = {0, 0, 1, -1};
    int dy[]  = {1, -1, 0, 0};
    int total = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (bd[i][j] != '.') {
                total++;
            }
        }
    }
    function<bool(int, int, int)> check = [&](int x, int y, int direct) -> bool {
        vector<vector<int>> vis(r + 1, vector<int>(c + 1));
        int                 cnt = 0;
        while (true) {
            char cur = bd[x][y];
            if (cur == '/') {
                if (direct == 0) {
                    direct = 3;
                } else if (direct == 1) {
                    direct = 2;
                } else if (direct == 2) {
                    direct = 1;
                } else {
                    direct = 0;
                }
            } else if (cur == '\\') {
                if (direct == 0) {
                    direct = 2;
                } else if (direct == 1) {
                    direct = 3;
                } else if (direct == 2) {
                    direct = 0;
                } else {
                    direct = 1;
                }
            }
            if (cur == '/' || cur == '\\') {
                if (!vis[x][y]) {
                    cnt++;
                    vis[x][y]++;
                } else if (vis[x][y] >= 2) {
                    return cnt == total;
                }
            }
            x += dx[direct];
            y += dy[direct];
            if (x < 1 || x > r || y < 1 || y > c) {
                return cnt == total;
            }
        }
    };
    vector<string> ans;
    for (int i = 1; i <= r; i++) {
        if (check(i, 1, 0)) {
            ans.push_back(format("W{}", i));
        }
    }
    for (int i = 1; i <= r; i++) {
        if (check(i, c, 1)) {
            ans.push_back(format("E{}", i));
        }
    }
    for (int i = 1; i <= c; i++) {
        if (check(1, i, 2)) {
            ans.push_back(format("N{}", i));
        }
    }
    for (int i = 1; i <= c; i++) {
        if (check(r, i, 3)) {
            ans.push_back(format("S{}", i));
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << ' ';
    }
    return 0;
}
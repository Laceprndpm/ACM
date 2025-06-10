#include <deque>
#include <iostream>
#include <string>
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
    int h, w;
    cin >> h >> w;
    vector<string> bd(h);
    for (int i = 0; i < h; i++) {
        cin >> bd[i];
    }
    deque<i64> dq;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (bd[i][j] == 'E') dq.push_back(i * w + j);
        }
    }
    vector<vector<char>> vis(h, vector<char>(w));
    int                  dx[4] = {0, 0, -1, 1};
    int                  dy[4] = {1, -1, 0, 0};
    while (!dq.empty()) {
        i64 cur = dq.front();
        dq.pop_front();
        for (int i = 0; i < 4; i++) {
            i64 x = cur / w, y = cur % w;
            x += dx[i], y += dy[i];
            if (x < 0 || x >= h || y < 0 || y >= w) continue;
            if (bd[x][y] == '#') continue;
            if (vis[x][y] != '\0') continue;

            if (i == 0) {
                vis[x][y] = '<';
            } else if (i == 1) {
                vis[x][y] = '>';
            } else if (i == 2) {
                vis[x][y] = 'v';
            } else if (i == 3) {
                vis[x][y] = '^';
            }
            dq.push_back(x * w + y);
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (bd[i][j] == '.') {
                cout << vis[i][j];
            } else {
                cout << bd[i][j];
            }
        }
        cout << '\n';
    }
    return 0;
}
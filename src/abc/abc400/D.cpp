#include <deque>
#include <iostream>
#include <string>
#include <utility>
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
    int rowH, colW;
    cin >> rowH >> colW;
    vector<string>       board(rowH);
    vector<vector<int>>  dis(rowH, vector<int>(colW, INF));
    vector<vector<bool>> inQue(rowH, vector<bool>(colW, false));
    for (int i = 0; i < rowH; i++) {
        cin >> board[i];
    }
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    vector<int>           dx{0, 0, -2, 2, 1, -1, 0, 0};
    vector<int>           dy{-2, 2, 0, 0, 0, 0, 1, -1};
    deque<pair<int, int>> q;
    q.push_back({a, b});
    dis[a][b] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop_front();
        inQue[x][y] = false;
        for (int i = 0; i < 4; i++) {
            int mx = dx[i] + x, my = dy[i] + y;
            if (mx < 0 || mx >= rowH || my < 0 || my >= colW) {
                continue;
            }
            if (dis[mx][my] > dis[x][y] + 1) {
                dis[mx][my] = dis[x][y] + 1;
                if (!inQue[mx][my]) {
                    inQue[mx][my] = true;
                    q.push_back({mx, my});
                }
            }
        }
        for (int i = 4; i < 8; i++) {
            int mx = dx[i] + x, my = dy[i] + y;
            if (mx < 0 || mx >= rowH || my < 0 || my >= colW) {
                continue;
            }
            if (board[mx][my] == '.') {
                if (dis[mx][my] > dis[x][y]) {
                    dis[mx][my] = dis[x][y];
                    if (!inQue[mx][my]) {
                        inQue[mx][my] = true;
                        q.push_front({mx, my});
                    }
                }
            } else {
                if (dis[mx][my] > dis[x][y] + 1) {
                    dis[mx][my] = dis[x][y] + 1;
                    if (!inQue[mx][my]) {
                        inQue[mx][my] = true;
                        q.push_back({mx, my});
                    }
                }
            }
        }
    }
    cout << dis[c][d] << '\n';
    return 0;
}
#include <array>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using u128 = unsigned __int128;

// vectors
#define sz(x)   int(size(x))
#define bg(x)   begin(x)
#define all(x)  bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x)  sort(all(x))
#define rsz     resize
#define ins     insert
#define pb      push_back
#define eb      emplace_back
#define ft      front()
#define bk      back()

constexpr int INF = 1e9;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int h, w, k;
    cin >> h >> w >> k;
    vector<vector<array<int, 2>>> bd(h, vector<array<int, 2>>(w, {INF, INF}));
    vector<vector<int>>           vis(h, vector<int>(w));
    deque<pair<int, int>>         que;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        bd[r][c][0] = bd[r][c][1] = 0;
        que.push_back({r, c});
    }
    auto go = [&](int x, int y, int nx, int ny) {
        int d = bd[x][y][1];
        if (d + 1 < bd[nx][ny][0]) {
            bd[nx][ny][1] = bd[nx][ny][0];
            bd[nx][ny][0] = d + 1;
        } else if (d + 1 < bd[nx][ny][1]) {
            bd[nx][ny][1] = d + 1;
        }
    };
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop_front();
        if (vis[x][y]) continue;
        vis[x][y] = 1;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
            go(x, y, nx, ny);
            if (bd[nx][ny][1] < INF) {
                que.push_back({nx, ny});
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (bd[i][j][1] == INF) {
                ans += 0;
            } else {
                ans += bd[i][j][1];
            }
        }
    }
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
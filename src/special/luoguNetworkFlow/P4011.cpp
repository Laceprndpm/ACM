#include <bits/stdc++.h>

using namespace std;
using ll   = long long;
using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using i64  = long long;
using u64  = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;
using f128 = __float128;

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
#define mt      make_tuple
#define fi      first
#define se      second

constexpr int N = 11, M = 11, P = 10;
int           walldoor[N][M][N][M];
int           wall[N][M][N][M];
int           key[N][M];

void solve()
{
    int n, m, p;
    cin >> n >> m >> p;
    auto isvalid = [&](int x, int y) { return x >= 1 && y >= 1 && x <= n && y <= m; };
    int  K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int xi, yi, xj, yj, id;
        cin >> xi >> yi >> xj >> yj >> id;
        if (id == 0) {
            wall[xi][yi][xj][yj] = 1;
            wall[xj][yj][xi][yi] = 1;
        } else {
            walldoor[xi][yi][xj][yj] |= 1 << (id - 1);
            walldoor[xj][yj][xi][yi] |= 1 << (id - 1);
        }
    }
    int S;
    cin >> S;
    for (int i = 0; i < S; i++) {
        int xi, yi, qi;
        cin >> xi >> yi >> qi;
        key[xi][yi] |= 1 << (qi - 1);
    }
    const u32                              status = (1 << p) - 1;
    vector<vector<vector<int>>>            dis(status + 1ull,
                                               vector<vector<int>>(n + 1, vector<int>(m + 1, numeric_limits<int>::max())));
    deque<pair<int, tuple<u32, int, int>>> que;
    que.push_back({0, {0, 1, 1}});
    int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    while (!que.empty()) {
        auto [dist, pos] = que.front();
        que.pop_front();
        auto [curst, cur_x, cur_y] = pos;
        if (dis[curst][cur_x][cur_y] != numeric_limits<int>::max()) continue;
        dis[curst][cur_x][cur_y] = dist;
        for (int i = 0; i < 4; i++) {
            int nxt_x = cur_x + dx[i], nxt_y = cur_y + dy[i];
            if (!isvalid(nxt_x, nxt_y)) continue;
            if (wall[cur_x][cur_y][nxt_x][nxt_y]) continue;
            if ((walldoor[cur_x][cur_y][nxt_x][nxt_y] & int(curst)) != walldoor[cur_x][cur_y][nxt_x][nxt_y]) continue;
            u32 keyst = key[nxt_x][nxt_y];
            que.push_back({dist + 1, {curst | keyst, nxt_x, nxt_y}});
        }
    }
    int mndis = numeric_limits<int>::max();
    for (u32 i = 0; i <= status; i++) {
        mndis = min(mndis, dis[i][n][m]);
    }
    if (mndis == numeric_limits<int>::max()) {
        cout << -1 << '\n';
    } else {
        cout << mndis << '\n';
    }
}

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}

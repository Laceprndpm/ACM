#include <bits/stdc++.h>

#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>
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

void solve()
{
    constexpr int dx[] = {0, 0, -1, +1};
    constexpr int dy[] = {-1, +1, 0, 0};
    int           n, m;
    cin >> n >> m;
    vector<string> board(n);
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    bool is_solveable = [&]() -> bool {
        vector<vector<int>> visited(n, vector<int>(m));

        auto isValid = [&n, &m, &board](int x, int y) {
            return (0 <= x && x < n) && (0 <= y && y < m) && board[x][y] != '#';
        };
        auto dfs = [&](auto&& dfs, int x, int y) -> int {
            if (!isValid(x, y)) return 0;
            if (visited[x][y]) return 0;
            visited[x][y] = 1;
            int val       = 0;
            switch (board[x][y]) {
                case '@': val += 1; break;
                case '*': val -= 1; break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                val += dfs(dfs, nx, ny);
            }
            return val;
        };
        int ok = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (dfs(dfs, i, j) != 0) {
                    ok = 0;
                }
            }
        }
        return ok;
    }();
    if (!is_solveable) {
        cout << -1 << '\n';
        return;
    }
    vector<array<int, 3>> ans_string;

    auto bfs = [&](const int x, const int y) -> void {
        auto isValid = [&n, &m, &board](int x, int y) {
            return (0 <= x && x < n) && (0 <= y && y < m) && board[x][y] != '#';
        };
        vector<vector<int>>         father(n, vector<int>(m, {-1}));
        deque<tuple<int, int, int>> que;
        que.push_back({x, y, 4});
        int ax, ay;
        while (true) {
            assert(!que.empty());
            auto [cx, cy, sta] = que.front();
            que.pop_front();
            if (!isValid(cx, cy)) continue;
            if (father[cx][cy] != -1) continue;
            father[cx][cy] = sta;
            if (board[cx][cy] == '@') {
                ax = cx;
                ay = cy;
                break;
            }
            for (int i = 0; i < 4; i++) {
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                que.push_back({nx, ny, i});
            }
        }
        int destx = ax, desty = ay;

        vector<vector<array<int, 3>>> tmp_ans;
        vector<array<int, 3>>         cur_string;
        while (true) {
            if (board[ax][ay] == '!') {
                tmp_ans.push_back(cur_string);
                cur_string.clear();
            }
            if (ax == x && ay == y) {
                tmp_ans.push_back(cur_string);
                break;
            }
            assert(!(board[ax][ay] == '@' && ax != destx && ay != desty));
            assert(father[ax][ay] != 4);
            int sta = father[ax][ay] ^ 1;
            cur_string.push_back({ax, ay, sta});
            ax = ax + dx[sta];
            ay = ay + dy[sta];
        }
        reverse(all(tmp_ans));
        for (auto& it : tmp_ans) {
            ans_string.insert(ans_string.end(), it.begin(), it.end());
        }
        board[destx][desty] = '.';
        board[x][y]         = '!';
    };
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '*') {
                bfs(i, j);
            }
        }
    }
    cout << ans_string.size() << '\n';
    constexpr char cx[] = {'L', 'R', 'U', 'D'};
    for (auto& it : ans_string) {
        cout << it[0] + 1 << ' ' << it[1] + 1 << ' ' << cx[it[2]];
        cout << '\n';
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

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
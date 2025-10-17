#include <deque>
#include <iostream>
#include <utility>
#include <vector>
#ifndef CLANGD_MODE
#ifndef DEBUG
#define NDEBUG
#undef assert
#define assert(x) [[assume(x)]]
#include <bits/stdc++.h>
#endif
#endif
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
    int h, w;
    cin >> h >> w;
    vector<string> board(h + 2);
    for (int i = 1; i <= h; i++) {
        cin >> board[i];
        board[i] = '.' + board[i] + '.';
    }
    board[0] = board[h + 1]    = string(w + 2, '.');
    int                   dx[] = {0, 0, -1, 1};
    int                   dy[] = {1, -1, 0, 0};
    deque<pair<int, int>> current;
    deque<pair<int, int>> nxt;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (board[i][j] == '#') {
                current.pb({i, j});
            }
        }
    }
    while (!current.empty()) {
        for (auto [i, j] : current) {
            for (int k = 0; k < 4; k++) {
                int cnt = 0;
                if (i + dx[k] <= 0 || i + dx[k] > h || j + dy[k] <= 0 || j + dy[k] > w
                    || board[i + dx[k]][j + dy[k]] == '#')
                    continue;
                for (int kk = 0; kk < 4; kk++) {
                    cnt += (board[i + dx[k] + dx[kk]][j + dy[k] + dy[kk]] == '#');
                }
                if (cnt == 1) {
                    nxt.pb({i + dx[k], j + dy[k]});
                }
            }
        }
        for (auto [u, v] : nxt) {
            board[u][v] = '#';
        }
        current = std::move(nxt);
        nxt.clear();
    }
    int cnt = 0;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            if (board[i][j] == '#') cnt++;
        }
    }
    cout << cnt;
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
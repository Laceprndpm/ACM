#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using i64          = long long;
using PII          = pair<int, int>;
constexpr int  INF = 1e9;
vector<string> board;
i64            n, m;
vector<i64>    vis;

i64 compose(i64 i, i64 j, i64 u, i64 v)
{
    return i * m * n * m + j * n * m + u * m + v;
}

void decompose(i64 code, i64 &i, i64 &j, i64 &u, i64 &v)
{
    i = code / (m * n * m);
    code %= (m * n * m);
    j = code / (n * m);
    code %= (n * m);
    u = code / m;
    code %= m;
    v = code;
}

int check(int i, int j)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            if (board[r][c] == '.') {
                if (i == r && j == c) continue;
                int msk = compose(i, j, r, c);
                if (vis[msk] == -1) bfs(msk);
                if (!flag[vis[msk]]) return 0;
            }
    return 1;
}

void init(int n, int m)
{
    board.clear();
    board.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> board[i];
    }
    vis.clear();
    vis.resize(n * m * n + 3, -1);
}

void solve()
{
    cin >> n >> m;
    init(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
        }
    }
}

signed main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
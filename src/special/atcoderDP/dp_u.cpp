#include <iostream>
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
    i64 n;
    cin >> n;
    const int           N = 1 << n;
    vector<vector<i64>> board(n, vector<i64>(n));
    vector<i64>         setVal(N);
    vector<int>         vis(N);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < N; i++) {
        for (int r = 0; r < n; r++) {
            if (!(i >> r & 1)) continue;
            for (int c = r; c < n; c++) {
                if (!(i >> c & 1)) continue;
                setVal[i] += board[r][c];
            }
        }
    }
    vector<i64> dp(N);
    auto        dfs = [&](auto&& dfs, int mark) -> i64 {
        if (vis[mark]) return dp[mark];
        vis[mark] = 1;
        i64 val   = setVal[mark];
        for (int s = mark; s; s = (s - 1) & mark) {
            if (s == mark) continue;
            if (s == 0) break;
            val = max(val, dfs(dfs, s) + dfs(dfs, s ^ mark));
        }
        return dp[mark] = val;
    };
    cout << dfs(dfs, N - 1);
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
#include <algorithm>
#include <iostream>
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
#define int     long long
constexpr int       INF = 1e18;
vector<vector<int>> bd;

// vector<vector<int>> dp;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    bd.resize(n);
    for (auto& i : bd) {
        i.assign(m + 1, INF);
    }
    // dp = bd;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> bd[i][j];
        }
    }
    // dp[0][0] = 0;
    vector<int> cur_dp(m), nxt_dp(m);
    fill(all(cur_dp), INF);
    fill(all(nxt_dp), INF);
    cur_dp[0] = 0;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> least_dist(m, vector<int>(m + 1));
        for (int j = 0; j < m; j++) {
            least_dist[j][0] = bd[i][j];
            for (int k = 1; k <= m; k++) {
                least_dist[j][k] = least_dist[j][k - 1] + bd[i][(j + k) % m];
            }
        }
        for (int j = 2 * m; j >= 0; j--) {
            for (int jj = 0; jj <= m; jj++) {
                least_dist[j % m][jj] = min(k + least_dist[(j + 1) % m][jj], least_dist[j % m][jj]);
            }
        }
        for (int j = 0; j < m; j++) {
            for (int f = 0; f <= j; f++) {
                nxt_dp[j] = min(nxt_dp[j], cur_dp[f] + least_dist[f][j - f]);
            }
        }
        swap(cur_dp, nxt_dp);
        fill(all(nxt_dp), INF);
    }
    cout << cur_dp[m - 1] << '\n';
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
    int t;
    cin >> t;
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
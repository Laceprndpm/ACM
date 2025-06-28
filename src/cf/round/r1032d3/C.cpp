#include <algorithm>
#include <iostream>
#include <set>
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

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> bd(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> bd[i][j];
        }
    }
    vector<pair<int, int>> candi;
    int                    curmax = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (bd[i][j] > curmax) {
                curmax = bd[i][j];
                candi.clear();
            }
            if (bd[i][j] == curmax) {
                candi.push_back({i, j});
            }
        }
    }
    // vector<vector<int>> cnt(n, vector<int>(m));
    vector<vector<int>> cnt(n, vector<int>(m));
    vector<int>         row(n);
    vector<int>         col(m);
    for (auto i : candi) {
        cnt[i.first][i.second]++;
        row[i.first]++;
        col[i.second]++;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row[i] + col[j] - cnt[i][j] == sz(candi)) {
                cout << curmax - 1 << '\n';
                return;
            }
        }
    }
    cout << curmax << '\n';
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
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

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    k--;
    vector<string>      bd(n + 1);
    vector<vector<int>> cnt(n + 2, vector<int>(m + 2));
    for (int i = 1; i <= n; i++) {
        cin >> bd[i];
        bd[i] = '0' + bd[i];
    }
    auto relax = [&](int& x, int& y) {
        x = max(x, 0), y = max(y, 0);
        x = min(x, n + 1), y = min(y, m + 1);
    };
    i64 ans1 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (bd[i][j] == 'g') {
                ans1++;
                int lf1 = i - k, lf2 = j - k;
                relax(lf1, lf2);
                cnt[lf1][lf2]++;
                int rf1 = i - k, rf2 = j + k + 1;
                relax(rf1, rf2);
                cnt[rf1][rf2]--;
                int lb1 = i + k + 1, lb2 = j - k;
                relax(lb1, lb2);
                cnt[lb1][lb2]--;
                int rb1 = i + k + 1, rb2 = j + k + 1;
                relax(rb1, rb2);
                cnt[rb1][rb2]++;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cnt[i][0] += cnt[i - 1][0];
    }
    for (int j = 1; j <= m; j++) {
        cnt[0][j] += cnt[0][j - 1];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cnt[i][j] += cnt[i - 1][j] + cnt[i][j - 1] - cnt[i - 1][j - 1];
        }
    }
    i64 ans2 = ans1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (bd[i][j] == '.') {
                ans2 = min<i64>(ans2, cnt[i][j]);
            }
        }
    }
    cout << ans1 - ans2 << '\n';
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
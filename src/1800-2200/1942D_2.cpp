#include <array>
#include <iostream>
#include <queue>
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

struct node {};

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<i64>> dp(n + 1);
    vector<vector<i64>> bd(n + 1, vector<i64>(n + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> bd[i][j];
        }
    }
    dp[0] = {0};
    for (int i = 1; i <= n; i++) {
        priority_queue<array<i64, 3>> pq;  // val, which dp, dp idx

        for (int j = i - 2; j >= -1; j--) {
            pq.push({(j < 0 ? 0 : dp[j][0]) + bd[j + 2][i], j, 0});
        }

        pq.push({dp[i - 1][0], i - 1, 0});

        while (!pq.empty() && dp[i].size() < k) {
            auto [val, dpIdx, idx] = pq.top();
            pq.pop();

            dp[i].push_back(val);

            if (dpIdx < 0 || idx + 1 >= dp[dpIdx].size()) continue;

            i64 valNext;
            if (dpIdx == i - 1) {
                valNext = dp[dpIdx][idx + 1];
            } else {
                valNext = bd[dpIdx + 2][i] + dp[dpIdx][idx + 1];
            }
            pq.push({valNext, dpIdx, idx + 1});
        }
    }
    for (int i : dp[n]) {
        cout << i << ' ';
    }
    cout << '\n';
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
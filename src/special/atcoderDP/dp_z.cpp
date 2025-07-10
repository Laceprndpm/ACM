#include <deque>
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
    i64 n, c;
    cin >> n >> c;
    vector<i64> hi(n);
    vector<i64> dp(n);
    deque<i64>  que_idx;
    que_idx.pb(0);
    for (auto& i : hi) {
        cin >> i;
    }
    auto slope = [&](int idx1, int idx2) -> double {
        return (double)(dp[idx1] + hi[idx1] * hi[idx1] - dp[idx2] - hi[idx2] * hi[idx2]) / (hi[idx1] - hi[idx2]);
    };
    for (int i = 1; i < n; i++) {
        while ((que_idx.size() >= 2)) {
            int head = que_idx[0], head2 = que_idx[1];
            if (!(slope(head, head2) <= 2ll * hi[i])) break;
            que_idx.pop_front();
        }
        int j = que_idx.front();
        dp[i] = dp[j] + (hi[i] - hi[j]) * (hi[i] - hi[j]) + c;
        while (sz(que_idx) >= 2) {
            int tail_idx = sz(que_idx) - 1;
            int tail     = que_idx[tail_idx];
            int tail2    = que_idx[tail_idx - 1];
            if (!((slope(tail2, tail)) >= slope(tail, i))) break;
            que_idx.pop_back();
        }
        que_idx.eb(i);
    }
    cout << dp[n - 1];
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
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
    int n, m;
    cin >> n >> m;
    vector<i64> xi(n);
    for (i64& i : xi) {
        cin >> i;
    }
    sor(xi);
    vector<i64> gaps;
    for (int i = 0; i < n - 1; i++) {
        gaps.eb(xi[i + 1] - xi[i]);
    }
    sor(gaps);
    i64 ans = accumulate(bg(gaps), bg(gaps) + n - m, 0ll);
    cout << ans << '\n';
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
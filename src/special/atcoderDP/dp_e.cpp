#include <algorithm>
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

constexpr i64 INF = 1e16;

signed main(signed argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef BATCH
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
#endif
    int n, w;
    cin >> n >> w;
    vector<i64> val(1e5 + 50, INF);
    val[0] = 0;
    for (int i = 0; i < n; i++) {
        int weight, value;
        cin >> weight >> value;
        for (int j = 1e5; j >= 0; j--) {
            if (j - value >= 0) val[j] = min(val[j], val[j - value] + weight);
            val[j] = min(val[j], val[j + 1]);
        }
    }
    int ans = upper_bound(all(val), w) - bg(val) - 1;
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
#include <iostream>
#include <map>
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
    i64 ans = 0;
    i64 n, s, x;
    cin >> n >> s >> x;
    vector<i64> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    map<i64, i64> mp;
    vector<i64>   candi;
    i64           prefix = 0;
    candi.eb(prefix);
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) {
            for (i64 i : candi) {
                mp[i]++;
            }
            candi.clear();
        }
        if (arr[i] > x) {
            mp.clear();
            candi.clear();
        }
        prefix += arr[i];
        ans += mp[prefix - s];
        candi.eb(prefix);
    }
    cout << ans << '\n';
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
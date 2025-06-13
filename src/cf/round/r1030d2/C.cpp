#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using i64  = long long;
using u64  = unsigned long long;
using u32  = unsigned;
using i128 = unsigned __int128;
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
    i64 n, k;
    cin >> n >> k;
    vector<i64> arr(n);
    vector<i64> tmp;
    tmp.reserve(5000 * 64);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        i64 cur = arr[i];
        for (int j = 0; j < 31; j++) {
            i64 bitmask = 1ll << j;
            if ((bitmask & cur) == 0) {
                tmp.emplace_back(bitmask);
            } else {
                ans++;
            }
        }
        for (int j = 31; j <= 60; j++) {
            tmp.emplace_back(1ll << j);
        }
    }
    sor(tmp);
    int          len = sz(tmp);
    vector<i128> prefix(len + 1);
    for (int i = 0; i < len; i++) {
        prefix[i + 1] = prefix[i] + tmp[i];
    }
    i64 addnum = upper_bound(prefix.begin(), prefix.end(), k) - prefix.begin() - 1;
    cout << addnum + ans << '\n';
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
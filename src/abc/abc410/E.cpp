#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
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
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> Harr(n), Marr(n);
    for (int i = 0; i < n; i++) {
        cin >> Harr[i] >> Marr[i];
    }
    auto check = [&](int x) -> bool {
        if (x > n) return false;
        vector<int> health(h + 1);
        for (int i = 0; i < x; i++) {
            for (int j = h; j >= Harr[i]; j--) {
                health[j] = max(health[j], health[j - Harr[i]] + Marr[i]);
            }
        }
        i64 sumM = accumulate(bg(Marr), bg(Marr) + x, 0ll);
        if (sumM - health[h] <= m)
            return true;
        else
            return false;
    };
    int l = 0, r = n;
    int ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            l   = mid + 1;
        } else {
            r = mid - 1;
        }
    }
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
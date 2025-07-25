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

constexpr int INF = 1e9;

void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int         mx = *max_element(all(arr));
    vector<i64> ans(mx + 1);
    for (int i = 0; i < n; i++) {
        i64 ci = 0;
        if (i == 0 || arr[i] > arr[i - 1]) {
            ci++;
        }
        if (i + 1 < n && arr[i] < arr[i + 1]) {
            ci--;
        }
        int l = 1;
        while (l <= mx) {
            int val = (arr[i] - 1) / l;
            int r;
            if (val)
                r = (arr[i] - 1) / val + 1;
            else
                r = mx + 1;
            ans[l - 1] += (val + 1) * ci;
            ans[r - 1] -= (val + 1) * ci;
            l = r;
        }
        // int r = arr[i];
        // ans[r] += ci;
        // while (r > 0) {
        //     int val = (arr[i] - 1) / r + 1;
        //     int l   = (arr[i] - 1) / val + 1;
        //     ans[l - 1] += ci * val;
        //     ans[r] -= ci * val;
        //     r = l - 1;
        // }
    }
    for (int i = 0; i < mx; i++) {
        ans[i + 1] += ans[i];
    }
    for (int i = 0; i < mx; i++) {
        cout << ans[i] << " \n"[i == mx];
    }
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
    int t = 1;
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
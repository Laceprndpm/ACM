#include <algorithm>
#include <cassert>
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
    vector<int> arr(n), brr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> brr[i];
    }
    vector<int> prefix_min_a(n + 1, INF), prefix_min_b(n + 1, INF);
    for (int i = 0; i < n; i++) {
        prefix_min_b[i + 1] = min(prefix_min_b[i], brr[i]);
    }
    auto check = [&](int x) -> bool {
        int cnt = 0;
        for (int i = 0; i < x; i++) {
            if (arr[i] < prefix_min_b[n - x + 1]) {
                cnt++;
            }
        }
        bool has = 0;
        for (int i = x; i < n; i++) {
            if (arr[i] > prefix_min_b[n - x + 1]) {
                has = 1;
            }
        }
        return (has && cnt <= 1) || (cnt == 0);
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
    // auto itm = min_element(all(brr));
    // for (int i = 0; i < n; i++) {
    //     if (arr[i] < *itm) {
    //         for (int j = n - 1; j > i; j--) {
    //             if (arr[j] > *itm) {
    //                 swap(arr[i], arr[j]);
    //                 break;
    //             }
    //         }
    //     }
    // }
    // int i = 0, j = 0;
    // while (i < n && j < n) {
    //     if (arr[i] > brr[j]) {
    //         i++;
    //     } else if (arr[i] < brr[j]) {
    //         j++;
    //     } else {
    //         assert(0);
    //     }
    // }
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